#!/bin/sh

MAKE=${MAKE-make}

RUMPOBJ=${PWD}/rumpobj
RUMP=${RUMPOBJ}/rump
RUMPSRC=rumpsrc
OUTDIR=${PWD}/rump

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
	printf "\t-L: libraries to link eg net_netinet,net_netinet6. default all\n"
	printf "\t-p: huge page size to use eg 2M or 1G\n"
	printf "\t-s: location of source tree.  default: PWD/rumpsrc\n"
	printf "\t-o: location of object files. defaule PWD/rumpobj\n"
	printf "\t-d: location of installed files. defaule PWD/rump\n"
	printf "\tseccomp|noseccomp: select Linux seccomp (default off)\n"
	printf "\tcapsicum|nocapsicum: select FreeBSD capsicum (default on)\n"
	printf "\tdeterministic: make deterministic\n"
	printf "\tnotests: do not run tests\n"
	printf "Other options are passed to buildrump.sh\n"
	printf "\n"
	printf "Supported platforms are currently: linux, netbsd, freebsd, qemu-arm\n"
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

while getopts '?d:F:Hhj:L:o:p:qs:V:' opt; do
	case "$opt" in
	"d")
		mkdir -p ${OPTARG}
		OUTDIR=$(abspath ${OPTARG})
		;;
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
	"L")
		LIBS="${OPTARG}"
		;;
	"o")
		mkdir -p ${OPTARG}
		RUMPOBJ=$(abspath ${OPTARG})
		RUMP=${RUMPOBJ}/rump
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
	-k -s ${RUMPSRC} -o ${RUMPOBJ} -d ${RUMP} \
	${BUILD_QUIET} ${STDJ} ${EXTRAFLAGS} \
	tools build kernelheaders install

# remove libraries that are not/will not work
rm -f ${RUMP}/lib/librumpdev_ugenhc.a
rm -f ${RUMP}/lib/librumpfs_syspuffs.a
rm -f ${RUMP}/lib/librumpkern_sysproxy.a
rm -f ${RUMP}/lib/librumpnet_shmif.a
rm -f ${RUMP}/lib/librumpnet_sockin.a
rm -f ${RUMP}/lib/librumpvfs_fifofs.a
rm -f ${RUMP}/lib/librumpdev_netsmb.a
rm -f ${RUMP}/lib/librumpfs_smbfs.a
rm -f ${RUMP}/lib/librumpdev_usb.a
rm -f ${RUMP}/lib/librumpdev_ucom.a
rm -f ${RUMP}/lib/librumpdev_ulpt.a
rm -f ${RUMP}/lib/librumpdev_ubt.a
rm -f ${RUMP}/lib/librumpkern_sys_linux.a
rm -rf ${RUMP}/lib/pkgconfig

CFLAGS="${EXTRA_CFLAGS} ${DBG_F} ${HUGEPAGESIZE}" \
	AFLAGS="${EXTRA_AFLAGS} ${DBG_F}" \
	ASFLAGS="${AFLAGS}" \
	LDFLAGS="${EXTRA_LDFLAGS}" \
	CPPFLAGS="${EXTRA_CPPFLAGS}" \
	RUMPOBJ="${RUMPOBJ}" \
	RUMP="${RUMP}" \
	${MAKE} OS=${OS} DETERMINISTIC=${DETERMINISTIC} -C libc

CFLAGS="${EXTRA_CFLAGS} ${DBG_F}" \
	LDFLAGS="${EXTRA_LDFLAGS}" \
	CPPFLAGS="${EXTRA_CPPFLAGS}" \
	RUMPOBJ="${RUMPOBJ}" \
	RUMP="${RUMP}" \
	${MAKE} -C librumpuser

if [ ${FILTER-x} = "-DSECCOMP" ]; then LDLIBS="-lseccomp"; fi
CPPFLAGS="${EXTRA_CPPFLAGS} ${FILTER}" \
	CFLAGS="${EXTRA_CFLAGS} ${DBG_F}" \
	LDFLAGS="${EXTRA_LDFLAGS}" \
	LDLIBS="${LDLIBS}" \
	RUMPOBJ="${RUMPOBJ}" \
	RUMP="${RUMP}" \
	${MAKE} OS=${OS} -C tools

# for now just build libc
NETBSDLIBS="${RUMPSRC}/lib/libc ${RUMPSRC}/lib/libm ${RUMPSRC}/lib/libpthread"

RUMPMAKE=${RUMPOBJ}/tooldir/rumpmake

usermtree ${RUMP}
userincludes ${RUMPSRC} ${NETBSDLIBS}

for lib in ${NETBSDLIBS}; do
	makeuserlib ${lib}
done

# find which libs we should link
ALL_LIBS="${RUMP}/lib/librump.a
	${RUMP}/lib/librumpdev*.a
	${RUMP}/lib/librumpnet*.a
	${RUMP}/lib/librumpfs*.a
	${RUMP}/lib/librumpvfs*.a
	${RUMP}/lib/librumpkern*.a"

if [ ! -z ${LIBS+x} ]
then
	ALL_LIBS="${RUMP}/lib/librump.a"
	for l in $(echo ${LIBS} | tr "," " ")
	do
		case ${l} in
		dev_*)
			appendvar ALL_LIBS "${RUMP}/lib/librumpdev.a"
			;;
		net_*)
			appendvar ALL_LIBS "${RUMP}/lib/librumpnet.a ${RUMP}/lib/librumpnet_net.a"
			;;
		vfs_*)
			appendvar ALL_LIBS "${RUMP}/lib/librumpvfs.a"
			;;
		fs_*)
			appendvar ALL_LIBS "${RUMP}/lib/librumpvfs.a"
			;;
		esac
		appendvar ALL_LIBS "${RUMP}/lib/librump${l}.a"
	done
fi

# explode and implode
rm -rf ${RUMPOBJ}/explode
mkdir -p ${RUMPOBJ}/explode/libc
mkdir -p ${RUMPOBJ}/explode/rumpkernel
mkdir -p ${RUMPOBJ}/explode/rumpuser
mkdir -p ${RUMPOBJ}/explode/franken
(
	cd ${RUMPOBJ}/explode/libc
	${AR-ar} x ${RUMP}/lib/libc.a

	# some franken .o file names conflict with libc
	cd ${RUMPOBJ}/explode/franken
	${AR-ar} x ${RUMP}/lib/libfranken.a;
	for f in *.o
	do
		[ -f ../libc/$f ] && mv $f franken_$f
	done

	cd ${RUMPOBJ}/explode/rumpkernel
	for f in ${ALL_LIBS}
	do
		${AR-ar} x $f
	done
	${CC-cc} -nostdlib -Wl,-r *.o -o rumpkernel.o

	cd ${RUMPOBJ}/explode/rumpuser
	${AR-ar} x ${RUMP}/lib/librump.a
	${AR-ar} x ${RUMP}/lib/librumpuser.a

	cd ${RUMPOBJ}/explode
	${AR-ar} cr libc.a rumpkernel/rumpkernel.o rumpuser/*.o libc/*.o franken/*.o
)

# install to OUTDIR
${INSTALL-install} -d ${OUTDIR}/bin ${OUTDIR}/lib ${OUTDIR}/include
${INSTALL-install} ${RUMP}/bin/rumprun ${OUTDIR}/bin
${INSTALL-install} ${RUMP}/lib/libm.a ${RUMP}/lib/libpthread.a ${OUTDIR}/lib
${INSTALL-install} ${RUMP}/lib/*.o ${OUTDIR}/lib
${INSTALL-install} ${RUMPOBJ}/explode/libc.a ${OUTDIR}/lib
# permissions set wrong
chmod -R ug+rw ${RUMP}/include/*
cp -a ${RUMP}/include/* ${OUTDIR}/include

if [ ${RUNTESTS} = "test" ]; then
	CFLAGS="${EXTRA_CFLAGS} ${DBG_F}" \
		LDFLAGS="${EXTRA_LDFLAGS}" \
		CPPFLAGS="${EXTRA_CPPFLAGS}" \
		RUMPOBJ="${RUMPOBJ}" \
		OUTDIR="${OUTDIR}" \
		${MAKE} OS=${OS} test
fi
