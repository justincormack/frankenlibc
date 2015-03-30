#!/bin/sh

MAKE=${MAKE-make}

RUMPOBJ=${PWD}/rumpobj
RUMPSRC=rumpsrc

RUNTESTS="test"

TARGET=$(LC_ALL=C ${CC-cc} -v 2>&1 | sed -n 's/^Target: //p' )

case ${TARGET} in
*-linux*)
	OS=linux
	FILTER="-DNOSECCOMP"
	;;
*-netbsd*)
	OS=netbsd
	;;
*-freebsd*)
	OS=freebsd
	FILTER="-DCAPSICUM"
	;;
*)
	OS=unknown
esac

STDJ="-j 4"
BUILD_QUIET="-qq"
DBG_F='-O2 -g'

helpme()
{
	printf "Usage: $0 [-h] [options] [platform]\n"
	printf "supported options:\n"
	printf "\t-p: huge page size to use eg 2M or 1G\n"
	printf "\t-s: location of source tree.  default: PWD/rumpsrc\n"
	printf "\t-o: location of object files. defaule PWD/rumpobj\n"
	printf "\tseccomp|noseccomp: select Linux seccomp (default off)\n"
	printf "\tcapsicum|nocapsicum: select FreeBSD capsicum (default on)\n"
	printf "\tdeterministic: make deterministic\n"
	printf "\tnotests: do not run tests\n"
	printf "Other options are passed to buildrump.sh\n"
	printf "\n"
	printf "Supported platforms are currently: linux, netbsd, freebsd\n"
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

abspath() {
    cd "$1"
    printf "$(pwd)"
}

appendvar_fs ()
{
	vname="${1}"
	fs="${2}"
	shift 2
	if [ -z "$(eval echo \${$vname})" ]; then
		eval ${vname}="\${*}"
	else
		eval ${vname}="\"\${${vname}}"\${fs}"\${*}\""
	fi
}

appendvar ()
{

	vname="$1"
	shift
	appendvar_fs "${vname}" ' ' $*
}

[ ! -f ./buildrump.sh/subr.sh ] && git submodule update --init buildrump.sh

if [ ${RUMPSRC} = "rumpsrc" ]; then
	[ ! -f rumpsrc/build.sh ] && git submodule update --init rumpsrc
fi

. ./buildrump.sh/subr.sh

while getopts '?F:Hhj:o:p:qs:V:' opt; do
	case "$opt" in
	"F")
		EXTRAFLAGS="${EXTRAFLAGS} -F ${OPTARG}"
		ARG=${OPTARG#*=}
		case ${OPTARG} in
			CFLAGS\=*)
				appendvar EXTRA_CFLAGS "${ARG}"
				;;
			AFLAGS\=*)
				appendvar EXTRA_AFLAGS "${ARG}"
				;;
			LDFLAGS\=*)
				appendvar EXTRA_LDFLAGS "${ARG}"
				;;
			ACFLAGS\=*)
				appendvar EXTRA_CFLAGS "${ARG}"
				appendvar EXTRA_AFLAGS "${ARG}"
				;;
			ACLFLAGS\=*)
				appendvar EXTRA_CFLAGS "${ARG}"
				appendvar EXTRA_AFLAGS "${ARG}"
				appendvar EXTRA_LDFLAGS "${ARG}"
				;;
			CPPFLAGS\=*)
				appendvar EXTRA_CPPFLAGS "${ARG}"
				;;
			DBG\=*)
				appendvar F_DBG "${ARG}"
				;;
			CWARNFLAGS\=*)
				appendvar EXTRA_CWARNFLAGS "${ARG}"
				;;
			*)
				die Unknown flag: ${OPTARG}
				;;
		esac
		;;
	"H")
		EXTRAFLAGS="${EXTRAFLAGS} -H"
		;;
	"h")
		helpme
		;;
	"j")
		STDJ="-j ${OPTARG}"
		;;
	"o")
		mkdir -p ${OPTARG}
		RUMPOBJ=$(abspath ${OPTARG})
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
		FILTER="-DNOSECCOMP"
		;;
	"seccomp")
		FILTER="-DSECCOMP"
		;;
	"nocapsicum")
		FILTER="-DNOCAPSICUM"
		;;
	"capsicum")
		FILTER="-DCAPSICUM"
		;;
	"deterministic"|"det")
		DETERMINISTIC="deterministic"
		;;
	"test"|"tests")
		RUNTESTS="test"
		;;
	"notest"|"notests")
		RUNTESTS="notest"
		;;
	*)
		OS=${arg}
		;;
	esac
done

set -e

if [ "${OS}" = "unknown" ]; then
	die "Unknown or unsupported platform"
fi

[ -f libc/${OS}/platform.sh ] && . libc/${OS}/platform.sh

./buildrump.sh/buildrump.sh \
	-V RUMP_CURLWP=hypercall -V RUMP_LOCKS_UP=yes \
	-V MKPIC=no -V RUMP_KERNEL_IS_LIBC=1 \
	-F CFLAGS=-fno-stack-protector \
	-k -s ${RUMPSRC} -o ${RUMPOBJ} \
	${BUILD_QUIET} ${STDJ} ${EXTRAFLAGS} \
	tools build kernelheaders install

# remove libraries that are not/will not work
rm -f rump/lib/librumpdev_ugenhc.a
rm -f rump/lib/librumpfs_syspuffs.a
rm -f rump/lib/librumpkern_sysproxy.a
rm -f rump/lib/librumpnet_shmif.a
rm -f rump/lib/librumpnet_sockin.a
rm -f rump/lib/librumpvfs_fifofs.a
rm -f rump/lib/librumpdev_netsmb.a
rm -f rump/lib/librumpfs_smbfs.a
rm -f rump/lib/librumpdev_usb.a
rm -f rump/lib/librumpdev_ucom.a
rm -f rump/lib/librumpdev_ulpt.a
rm -f rump/lib/librumpdev_ubt.a
rm -rf rump/lib/pkgconfig

CFLAGS="${EXTRA_CFLAGS} ${DBG_F} ${HUGEPAGESIZE}" \
	AFLAGS="${EXTRA_AFLAGS} ${DBG_F}" \
	ASFLAGS="${AFLAGS}" \
	LDFLAGS="${EXTRA_LDFLAGS}" \
	CPPFLAGS="${EXTRA_CPPFLAGS}" \
	RUMPOBJ="${RUMPOBJ}" \
	${MAKE} OS=${OS} DETERMINISTIC=${DETERMINISTIC} -C libc

CFLAGS="${EXTRA_CFLAGS} ${DBG_F}" \
	LDFLAGS="${EXTRA_LDFLAGS}" \
	CPPFLAGS="${EXTRA_CPPFLAGS}" \
	RUMPOBJ="${RUMPOBJ}" \
	${MAKE} -C librumpuser

if [ ${FILTER-x} = "-DSECCOMP" ]; then LDLIBS="-lseccomp"; fi
CPPFLAGS="${EXTRA_CPPFLAGS} ${FILTER}" \
	CFLAGS="${EXTRA_CFLAGS} ${DBG_F}" \
	LDFLAGS="${EXTRA_LDFLAGS}" \
	LDLIBS="${LDLIBS}" \
	RUMPOBJ="${RUMPOBJ}" \
	${MAKE} OS=${OS} -C tools

# for now just build libc
LIBS="${RUMPSRC}/lib/libc ${RUMPSRC}/lib/libm ${RUMPSRC}/lib/libpthread"

RUMPMAKE=${RUMPOBJ}/tooldir/rumpmake

usermtree rump
userincludes ${RUMPSRC} ${LIBS}

for lib in ${LIBS}; do
	makeuserlib ${lib}
done

if [ ${RUNTESTS} = "test" ]; then
	CFLAGS="${EXTRA_CFLAGS} ${DBG_F}" \
		LDFLAGS="${EXTRA_LDFLAGS}" \
		CPPFLAGS="${EXTRA_CPPFLAGS}" \
		RUMPOBJ="${RUMPOBJ}" \
		${MAKE} OS=${OS} test
fi
