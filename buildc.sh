#!/bin/sh

MAKE=${MAKE-make}
CC=${CC-cc}
AR=${AR-ar}

OBJDIR=rumpobj

OS=${OS-"$($CC -v 2>&1| grep Target: | perl -p -e 's/.*(netbsd|linux).*/\1/')"}

STDJ="-j 8"
QUIET="-qq"

RUMPSRC=rumpsrc

[ ! -f ./buildrump.sh/subr.sh ] && git submodule update --init buildrump.sh
( [ ! -f rumpsrc/build.sh ] && git submodule update --init rumpsrc \
	&& cd rumpsrc && cat ../rumpuser.patch | patch -p1 )

set -e

. ./buildrump.sh/subr.sh

./buildrump.sh/buildrump.sh \
	-V RUMP_CURLWP=hypercall -V MKPIC=no -V RUMP_KERNEL_IS_LIBC=1 \
	-F CFLAGS=-fno-stack-protector \
	-k -N -s ${RUMPSRC} -o ${OBJDIR} ${QUIET} ${STDJ} \
	tools build kernelheaders install

RUMPMAKE=${PWD}/rumpobj/tooldir/rumpmake

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
