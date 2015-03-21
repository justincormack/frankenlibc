#!/bin/sh

MAKE=${MAKE-make}
CC=${CC-cc}

OBJDIR=rumpobj
RUMPSRC=rumpsrc

OS="unknown"
TOOLOS="unknown"

TARGET="$(${CC} -v 2>&1 | grep 'Target:' )"
if $(echo ${TARGET} | grep -q linux); then OS=linux
elif $(echo ${TARGET} | grep -q netbsd); then OS=netbsd
elif $(echo ${TARGET} | grep -q freebsd); then OS=freebsd
fi

STDJ="-j 8"
BUILD_QUIET="-qq"

helpme()
{
	printf "Usage: $0 [-h] [options] [platform]\n"
	printf "supported options:\n"
	printf "\t-p: huge page size to use eg 2M or 1G\n"
	printf "\t-s: location of source tree.  default: PWD/rumpsrc\n"
	printf "\tnoseccomp: disable Linux seccomp\n"
	printf "\tnocapsicum: disable FreeBSD capsicum\n"
	printf "\tdeterministic: make deterministic\n"
	printf "Other options are passed to buildrump.sh\n"
	printf "\n"
	printf "Supported platforms are currently: linux, netbsd\n"
	exit 1
}

bytes()
{
	value=$(echo "$1" | sed 's/[^0123456789].*$//g')
	units=$(echo "$1" | sed 's/^[0123456789]*//g')

	case "$units" in
	"kb"|"k"|"KB"|"K")
		value=$((${value} * 1024))
		;;
	"mb"|"m"|"MB"|"M")
		value=$((${value} * 1048576))
		;;
	"gb"|"g"|"GB"|"G")
		value=$((${value} * 1073741824))
		;;
	*)
		die "Bad huge page size"
		;;
	esac

	echo ${value}
}

while getopts '?F:Hhj:p:qs:V:' opt; do
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
	"p")
		SIZE=$(bytes ${OPTARG})
		HUGEPAGESIZE="-DHUGEPAGESIZE=${SIZE}"
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
	"noseccomp")
		TOOLOS="dummy"
		;;
	"nocapsicum")
		TOOLOS="dummy"
		;;
	"deterministic")
		DETERMINISTIC="deterministic"
		;;
	"det")
		DETERMINISTIC="deterministic"
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
	-V RUMP_CURLWP=hypercall -V RUMP_LOCKS_UP=yes \
	-V MKPIC=no -V RUMP_KERNEL_IS_LIBC=1 \
	-F CFLAGS=-fno-stack-protector \
	-k -s ${RUMPSRC} -o ${OBJDIR} \
	${BUILD_QUIET} ${STDJ} ${EXTRAFLAGS} \
	tools build kernelheaders install

export CFLAGS="${CFLAGS} -g ${HUGEPAGESIZE}"
export ASFLAGS="${ASFLAGS} -g"
export AFLAGS="${ASFLAGS}"

${MAKE} OS=${OS} -C libc

${MAKE} -C librumpuser

if [ ${TOOLOS} = "unknown" ]; then
	TOOLOS=${OS}
fi

${MAKE} OS=${TOOLOS} DETERMINISTIC=${DETERMINISTIC} -C tools

# for now just build libc
LIBS="${RUMPSRC}/lib/libc ${RUMPSRC}/lib/libm ${RUMPSRC}/lib/libpthread"

RUMPMAKE=${PWD}/rumpobj/tooldir/rumpmake

usermtree rump
userincludes ${RUMPSRC} ${LIBS}

for lib in ${LIBS}; do
	makeuserlib ${lib}
done

# tests

${MAKE} OS=${OS} -C libc test

RUMP_LIBS_FS="-lrumpfs_ffs -lrumpfs_cd9660 -lrumpdev_disk -lrumpdev -lrumpvfs"
RUMP_LIBS_NET="-lrumpnet_config -lrumpdev_bpf -lrumpnet_netinet -lrumpnet_netinet6 -lrumpnet_net -lrumpnet"

RUMP_LDLIBS="-Wl,--whole-archive ${RUMP_LIBS_NET} ${RUMP_LIBS_FS} -lrump -lrumpuser -Wl,--no-whole-archive"

LIBDIR="${PWD}/rump/lib"

TESTDIR="rumpobj/test"
mkdir -p ${TESTDIR}

${CC} ${CFLAGS} ${LDFLAGS} -static -nostdinc -Brump/lib -Irump/include -Lrump/lib test/hello.c -lc ${RUMP_LDLIBS} -lfranken -o ${TESTDIR}/test

export RUMP_VERBOSE=1

export BINDIR="rump/bin"

${BINDIR}/rumprun ${TESTDIR}/test
