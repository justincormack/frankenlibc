#!/bin/sh

MAKE=${MAKE-make}
CC=${CC-cc}

OBJDIR=rumpobj
RUMPSRC=rumpsrc

OS=unknown
TARGET="$(${CC} -v 2>&1 | grep 'Target:' )"
if $(echo ${TARGET} | grep -q linux); then OS=linux
elif $(echo ${TARGET} | grep -q netbsd); then OS=netbsd
fi

STDJ="-j 8"
BUILD_QUIET="-qq"

helpme()
{
	printf "Usage: $0 [-h] [options] [platform]\n"
	printf "supported options:\n"
	printf "\t-s: location of source tree.  default: PWD/rumpsrc\n"
	printf "Other options are passed to buildrump.sh\n"
	printf "\n"
	printf "Supported platforms are currently: linux, netbsd\n"
	exit 1
}

while getopts '?F:Hhj:qs:V:' opt; do
	case "$opt" in
	"F")
		EXTRAFLAGS="${EXTRAFLAGS} -F ${OPTARG}"
		;;
	"H")
		EXTRAFLAGS="${EXTRAFLAGS} -H"
		;;
	"h")
		helpme
		;;
	"j")
		STDJ=${OPTARG}
		;;
	"q")
		BUILD_QUIET=${BUILD_QUIET:=-}q
		;;
	"s")
		RUMPSRC=${OPTARG}
		;;
	"V")
		EXTRAFLAGS="${EXTRAFLAGS} -V ${OPTARG}"
		;;
	"?")
		helpme
		;;
	esac
done
shift $((${OPTIND} - 1))

for arg in "$@"; do
        case ${arg} in
	"clean")
		${MAKE} clean
		;;
	*)
		OS=${arg}
		;;
	esac
done

[ ! -f ./buildrump.sh/subr.sh ] && git submodule update --init buildrump.sh

if [ ${RUMPSRC} = "rumpsrc" ]; then
	[ ! -f rumpsrc/build.sh ] && git submodule update --init rumpsrc
fi

set -e

. ./buildrump.sh/subr.sh

if [ "${OS}" = "unknown" ]; then
	die "Unknown or unsupported platform"
fi

./buildrump.sh/buildrump.sh \
	-V RUMP_CURLWP=hypercall -V MKPIC=no -V RUMP_KERNEL_IS_LIBC=1 \
	-F CFLAGS=-fno-stack-protector \
	-k -N -s ${RUMPSRC} -o ${OBJDIR} \
	${BUILD_QUIET} ${STDJ} ${EXTRAFLAGS} \
	tools build kernelheaders install

CFLAGS=-g ASFLAGS=-g AFLAGS=-g ${MAKE} OS=${OS} -C libc test

CFLAGS=-g ${MAKE} -C librumpuser

# Build libs
#LIBS="$(stdlibs ${RUMPSRC})"
#if [ "$(${RUMPMAKE} -f rumptools/mk.conf -V '${_BUILDRUMP_CXX}')" = 'yes' ]
#then
#	LIBS="${LIBS} $(stdlibsxx ${RUMPSRC})"
#fi

# for now just build libc
LIBS="${RUMPSRC}/lib/libc ${RUMPSRC}/lib/libpthread"

RUMPMAKE=${PWD}/rumpobj/tooldir/rumpmake

usermtree rump
userincludes ${RUMPSRC} ${LIBS}

for lib in ${LIBS}; do
	makeuserlib ${lib}
done

# tests

RUMP_LIBS_FS="-lrumpfs_ffs -lrumpfs_cd9660 -lrumpdev_disk -lrumpdev -lrumpvfs"
RUMP_LIBS_NET="-lrumpnet_config -lrumpdev_bpf -lrumpnet_netinet -lrumpnet_netinet6 -lrumpnet_net -lrumpnet"

RUMP_LDLIBS="-Wl,--whole-archive ${RUMP_LIBS_NET} ${RUMP_LIBS_FS} -lrump -lrumpuser -Wl,--no-whole-archive"

LIBDIR="${PWD}/rump/lib"

TESTDIR="rumpobj/test"
mkdir -p ${TESTDIR}

${CC} -static -nostdinc -Brump/lib -Irump/include -Lrump/lib test/hello.c -lc ${RUMP_LDLIBS} -lfranken -o ${TESTDIR}/test

export RUMP_VERBOSE=1

${TESTDIR}/test
