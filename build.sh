#!/bin/sh

MAKE=${MAKE-make}

RUMPOBJ=${PWD}/rumpobj
RUMP=${RUMPOBJ}/rump
RUMPSRC=${PWD}/src
OUTDIR=${PWD}/rump
NCPU=1

RUNTESTS="test"
MAKETOOLS="yes"

TARGET=$(LC_ALL=C ${CC-cc} -v 2>&1 | sed -n 's/^Target: //p' )

case ${TARGET} in
*-linux*)
	OS=linux
	FILTER="-DNOSECCOMP"
	NCPU=$(nproc )
	;;
*-netbsd*)
	OS=netbsd
	NCPU=$(sysctl -n hw.ncpu )
	;;
*-freebsd*)
	OS=freebsd
	FILTER="-DCAPSICUM"
	NCPU=$(sysctl -n hw.ncpu )
	;;
*)
	OS=unknown
esac

STDJ="-j ${NCPU}"
BUILD_QUIET="-qq"
DBG_F='-O2 -g'

helpme()
{
	printf "Usage: $0 [-h] [options] [platform]\n"
	printf "supported options:\n"
	printf "\t-L: libraries to link eg net_netinet,net_netinet6. default all\n"
	printf "\t-m: hardcode rump memory limit. default from env or unlimited\n"
	printf "\t-M: thread stack size. default: 64k\n"
	printf "\t-p: huge page size to use eg 2M or 1G\n"
	printf "\t-r: release build, without debug settings\n"
	printf "\t-s: location of source tree.  default: PWD/rumpsrc\n"
	printf "\t-o: location of object files. defaule PWD/rumpobj\n"
	printf "\t-d: location of installed files. defaule PWD/rump\n"
	printf "\tseccomp|noseccomp: select Linux seccomp (default off)\n"
	printf "\tcapsicum|nocapsicum: select FreeBSD capsicum (default on)\n"
	printf "\tdeterministic: make deterministic\n"
	printf "\tnotests: do not run tests\n"
	printf "\tnotools: do not build extra tools\n"
	printf "\tclean: clean object directory first\n"
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
		die "Cannot understand value"
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

. ./buildrump/subr.sh

while getopts '?d:F:Hhj:L:M:m:o:p:qrs:V:' opt; do
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
		appendvar EXTRAFLAGS "-H"
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
	"M")
		size=$(bytes ${OPTARG})
		appendvar FRANKEN_FLAGS "-DSTACKSIZE=${size}"
		;;
	"m")
		size=$(bytes ${OPTARG})
		appendvar RUMPUSER_FLAGS "-DRUMP_MEMLIMIT=${size}"
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
	"r")
		DBG_F="-O2"
		appendvar EXTRAFLAGS "-r"
		;;
	"s")
		RUMPSRC=${OPTARG}
		;;
	"V")
		appendvar EXTRAFLAGS "-V ${OPTARG}"
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
	"tools")
		MAKETOOLS="yes"
		;;
	"notools")
		MAKETOOLS="no"
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

[ -f platform/${OS}/platform.sh ] && . platform/${OS}/platform.sh

./buildrump/buildrump.sh \
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
rm -f ${RUMP}/lib/librumpdev_umass.a

CFLAGS="${EXTRA_CFLAGS} ${DBG_F} ${HUGEPAGESIZE}" \
	AFLAGS="${EXTRA_AFLAGS} ${DBG_F}" \
	ASFLAGS="${EXTRA_AFLAGS} ${DBG_F}" \
	LDFLAGS="${EXTRA_LDFLAGS}" \
	CPPFLAGS="${EXTRA_CPPFLAGS}" \
	RUMPOBJ="${RUMPOBJ}" \
	RUMP="${RUMP}" \
	${MAKE} ${OS} -C platform

# should clean up how deterministic build is done
if [ ${DETERMINSTIC-x} = "deterministic" ]
then
	CFLAGS="${EXTRA_CFLAGS} ${DBG_F} ${HUGEPAGESIZE}" \
	AFLAGS="${EXTRA_AFLAGS} ${DBG_F}" \
	ASFLAGS="${EXTRA_AFLAGS} ${DBG_F}" \
	LDFLAGS="${EXTRA_LDFLAGS}" \
	CPPFLAGS="${EXTRA_CPPFLAGS}" \
	RUMPOBJ="${RUMPOBJ}" \
	RUMP="${RUMP}" \
	${MAKE} deterministic -C platform
fi 

CFLAGS="${EXTRA_CFLAGS} ${DBG_F} ${HUGEPAGESIZE}" \
	AFLAGS="${EXTRA_AFLAGS} ${DBG_F}" \
	ASFLAGS="${EXTRA_AFLAGS} ${DBG_F}" \
	LDFLAGS="${EXTRA_LDFLAGS}" \
	CPPFLAGS="${EXTRA_CPPFLAGS} ${FRANKEN_FLAGS}" \
	RUMPOBJ="${RUMPOBJ}" \
	RUMP="${RUMP}" \
	${MAKE} -C franken

CFLAGS="${EXTRA_CFLAGS} ${DBG_F}" \
	LDFLAGS="${EXTRA_LDFLAGS}" \
	CPPFLAGS="${EXTRA_CPPFLAGS} ${RUMPUSER_FLAGS}" \
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
	${MAKE} ${OS} -C tools

CFLAGS="${EXTRA_CFLAGS} ${DBG_F}" \
	LDFLAGS="${EXTRA_LDFLAGS}" \
	CPPFLAGS="${EXTRA_CPPFLAGS} ${RUMPUSER_FLAGS}" \
	RUMPOBJ="${RUMPOBJ}" \
	RUMP="${RUMP}" \
	${MAKE} -C libvirtif

# userspace libraries to build from NetBSD base
USER_LIBS="m pthread z crypt util prop rmt ipsec"
NETBSDLIBS="${RUMPSRC}/lib/libc"
for f in ${USER_LIBS}
do
	appendvar NETBSDLIBS "${RUMPSRC}/lib/lib${f}"
done

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
			appendvar ALL_LIBS "${RUMP}/lib/librumpvfs.a ${RUMP}/lib/librumpdev.a ${RUMP}/lib/librumpdev_disk.a"
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
mkdir -p ${RUMPOBJ}/explode/platform
(
	cd ${RUMPOBJ}/explode/libc
	${AR-ar} x ${RUMP}/lib/libc.a

	# some franken .o file names conflict with libc
	cd ${RUMPOBJ}/explode/franken
	${AR-ar} x ${RUMP}/lib/libfranken.a
	for f in *.o
	do
		[ -f ../libc/$f ] && mv $f franken_$f
	done

	# some platform .o file names conflict with libc
	cd ${RUMPOBJ}/explode/platform
	${AR-ar} x ${RUMP}/lib/libplatform.a
	for f in *.o
	do
		[ -f ../libc/$f ] && mv $f platform_$f
	done

	cd ${RUMPOBJ}/explode/rumpkernel
	for f in ${ALL_LIBS}
	do
		${AR-ar} x $f
	done
	${CC-cc} ${EXTRA_LDFLAGS} -nostdlib -Wl,-r *.o -o rumpkernel.o

	cd ${RUMPOBJ}/explode/rumpuser
	${AR-ar} x ${RUMP}/lib/librumpuser.a

	cd ${RUMPOBJ}/explode
	${AR-ar} cr libc.a rumpkernel/rumpkernel.o rumpuser/*.o libc/*.o franken/*.o platform/*.o
)

# install to OUTDIR
rm -rf ${OUTDIR}
${INSTALL-install} -d ${OUTDIR}/bin ${OUTDIR}/lib ${OUTDIR}/include
rm -rf ${OUTDIR}/bin/* ${OUTDIR}/lib/* ${OUTDIR}/include/*
${INSTALL-install} ${RUMP}/bin/rexec ${OUTDIR}/bin
(
	cd ${RUMP}/lib
	for f in ${USER_LIBS}
	do
		${INSTALL-install} ${RUMP}/lib/lib${f}.a ${OUTDIR}/lib
	done
)
${INSTALL-install} ${RUMP}/lib/*.o ${OUTDIR}/lib
[ -f ${RUMP}/lib/libg.a ] && ${INSTALL-install} ${RUMP}/lib/libg.a ${OUTDIR}/lib
${INSTALL-install} ${RUMPOBJ}/explode/libc.a ${OUTDIR}/lib
# permissions set wrong
chmod -R ug+rw ${RUMP}/include/*
cp -a ${RUMP}/include/* ${OUTDIR}/include

# create toolchain wrappers
# select these based on compiler defs
UNDEF="-D__NetBSD__ -D__RUMPRUN__"
[ ${OS} = "linux" ] && appendvar UNDEF "-Ulinux -U__linux -U__linux__ -U__gnu_linux__"
[ ${OS} = "freebsd" ] && appendvar UNDEF "-U__FreeBSD__"
appendvar UNDEF "-U_BIG_ENDIAN -U_LITTLE_ENDIAN"
if $(${CC-cc} -v 2>&1 | grep -q clang)
then
	TOOL_PREFIX=$(basename $(ls ${RUMPOBJ}/tooldir/bin/*-clang) | sed -e 's/-clang//' -e 's/--/-rumprun-/')
	# possibly some will need to be filtered if compiler complains. Also de-dupe.
	COMPILER_FLAGS="-fno-stack-protector ${EXTRA_CPPFLAGS} ${UNDEF} ${EXTRA_CFLAGS} ${EXTRA_LDSCRIPT_CC}"
	COMPILER_FLAGS="$(echo ${COMPILER_FLAGS} | sed 's/--sysroot=[^ ]*//g')"
	# set up sysroot to see if it works
	( cd ${OUTDIR} && ln -s . usr )
	LIBGCC="$(${CC-cc} ${EXTRA_CPPFLAGS} ${EXTRA_CFLAGS} -print-libgcc-file-name)"
	LIBGCCDIR="$(dirname ${LIBGCC})"
	ln -s ${LIBGCC} ${OUTDIR}/lib/
	ln -s ${LIBGCCDIR}/libgcc_eh.a ${OUTDIR}/lib/
	if ${CC-cc} -I${OUTDIR}/include --sysroot=${OUTDIR} -static ${COMPILER_FLAGS} tests/hello.c -o /dev/null 2>/dev/null
	then
		# can use sysroot with clang
		printf "#!/bin/sh\n\nexec ${CC-cc} --sysroot=${OUTDIR} -static ${COMPILER_FLAGS} \"\$@\"\n" > ${OUTDIR}/bin/${TOOL_PREFIX}-clang
	else
		# sysroot does not work with linker eg NetBSD
		appendvar COMPILER_FLAGS "-I${OUTDIR}/include -L${OUTDIR}/lib -B${OUTDIR}/lib"
		printf "#!/bin/sh\n\nexec ${CC-cc} -static ${COMPILER_FLAGS} \"\$@\"\n" > ${OUTDIR}/bin/${TOOL_PREFIX}-clang
	fi
	COMPILER="${TOOL_PREFIX}-clang"
	( cd ${OUTDIR}/bin
	  ln -s ${COMPILER} ${TOOL_PREFIX}-cc
	  ln -s ${COMPILER} rumprun-cc
	)
else
	# spec file for gcc
	TOOL_PREFIX=$(basename $(ls ${RUMPOBJ}/tooldir/bin/*-gcc) | sed -e 's/-gcc//' -e 's/--/-rumprun-/')
	COMPILER_FLAGS="-fno-stack-protector ${EXTRA_CFLAGS}"
	COMPILER_FLAGS="$(echo ${COMPILER_FLAGS} | sed 's/--sysroot=[^ ]*//g')"
	[ -f ${OUTDIR}/lib/crt0.o ] && appendvar STARTFILE "${OUTDIR}/lib/crt0.o"
	[ -f ${OUTDIR}/lib/crt1.o ] && appendvar STARTFILE "${OUTDIR}/lib/crt1.o"
	appendvar STARTFILE "${OUTDIR}/lib/crti.o"
	[ -f ${OUTDIR}/lib/crtbegin.o ] && appendvar STARTFILE "${OUTDIR}/lib/crtbegin.o"
	[ -f ${OUTDIR}/lib/crtbeginT.o ] && appendvar STARTFILE "${OUTDIR}/lib/crtbeginT.o"
	ENDFILE="${OUTDIR}/lib/crtend.o ${OUTDIR}/lib/crtn.o"
	cat tools/spec.in | sed \
		-e "s#@SYSROOT@#${OUTDIR}#g" \
		-e "s#@CPPFLAGS@#${EXTRA_CPPFLAGS}#g" \
		-e "s#@AFLAGS@#${EXTRA_AFLAGS}#g" \
		-e "s#@CFLAGS@#${EXTRA_CFLAGS}#g" \
		-e "s#@LDFLAGS@#${EXTRA_LDFLAGS}#g" \
		-e "s#@LDSCRIPT@#${EXTRA_LDSCRIPT}#g" \
		-e "s#@UNDEF@#${UNDEF}#g" \
		-e "s#@STARTFILE@#${STARTFILE}#g" \
		-e "s#@ENDFILE@#${ENDFILE}#g" \
		-e "s/--sysroot=[^ ]*//" \
		> ${OUTDIR}/lib/${TOOL_PREFIX}gcc.spec
	printf "#!/bin/sh\n\nexec ${CC-cc} -specs ${OUTDIR}/lib/${TOOL_PREFIX}gcc.spec ${COMPILER_FLAGS} -static -nostdinc -isystem ${OUTDIR}/include \"\$@\"\n" > ${OUTDIR}/bin/${TOOL_PREFIX}-gcc
	COMPILER="${TOOL_PREFIX}-gcc"
	( cd ${OUTDIR}/bin
	  ln -s ${COMPILER} ${TOOL_PREFIX}-cc
	  ln -s ${COMPILER} rumprun-cc
	)
fi
printf "#!/bin/sh\n\nexec ${AR-ar} \"\$@\"\n" > ${OUTDIR}/bin/${TOOL_PREFIX}-ar
printf "#!/bin/sh\n\nexec ${NM-nm} \"\$@\"\n" > ${OUTDIR}/bin/${TOOL_PREFIX}-nm
printf "#!/bin/sh\n\nexec ${OBJCOPY-objcopy} \"\$@\"\n" > ${OUTDIR}/bin/${TOOL_PREFIX}-objcopy
chmod +x ${OUTDIR}/bin/${TOOL_PREFIX}-*

# test for suplicated symbols

DUPSYMS=$(nm rump/lib/libc.a | grep ' T ' | sed 's/.* T //g' | sort | uniq -c -d)

if [ -n "${DUPSYMS}" ]
then
	printf "Duplicated symbols found:\n"
	echo ${DUPSYMS}
	exit 1
fi

# install some useful applications

mktool()
{
	cd ${RUMPSRC}/$2
	OBJDIR=${RUMPOBJ}/$1
	mkdir -p ${OBJDIR}

	LIBCRT0= \
	LIBCRTBEGIN= \
	LIBC="${OUTDIR}/lib/libc.a" \
	LIBUTIL="${OUTDIR}/lib/libutil.a" \
	LIBRMT="${OUTDIR}/lib/librmt.a" \
	MAKESYSPATH="${RUMPSRC}/share/mk" \
	DESTDIR=${OUTDIR} \
	MKDOC=no \
	MKMAN=no \
	MKRUMP=no \
		${RUMPOBJ}/tooldir/rumpmake CC="${OUTDIR}/bin/${COMPILER}" MAKEOBJDIR=${OBJDIR}
	${INSTALL-install} ${OBJDIR}/$1 ${OUTDIR}/bin/rump.$1
}

if [ ${MAKETOOLS} = "yes" ]
then
	( mktool pax bin/pax )
	( mktool newfs sbin/newfs )
	( mktool fsck_ffs sbin/fsck_ffs )
	( mktool mknod sbin/mknod )
	( mktool mkdir bin/mkdir )
	( mktool ls bin/ls )
	( mktool rm bin/rm )
	( mktool ln bin/ln )
	( mktool dd bin/dd )
	( mktool df bin/df )
	( mktool mount sbin/mount )
	( mktool ifconfig sbin/ifconfig )
	( mktool route sbin/route )
	( mktool ping sbin/ping )
	( mktool ping6 sbin/ping6 )
	( mktool rmdir bin/rmdir )
	( mktool chmod bin/chmod )
	( mktool chown sbin/chown )
	(
		cd ${OUTDIR}/bin
		ln rump.pax rump.tar
		ln rump.pax rump.cpio
	)
fi

if [ ${RUNTESTS} = "test" ]
then
	CC="${OUTDIR}/bin/${COMPILER}" \
		RUMPOBJ="${RUMPOBJ}" \
		OUTDIR="${OUTDIR}" \
		${MAKE} -C tests
fi
