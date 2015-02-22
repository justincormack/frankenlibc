#!/bin/sh

MAKE=${MAKE-make}
CC=${CC-cc}
AR=${AR-ar}

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
	-k -N -s ${RUMPSRC} ${QUIET} ${STDJ} \
	tools build kernelheaders install

RUMPMAKE=${PWD}/obj/tooldir/rumpmake

# -k build does not install rumpuser headers
mkdir -p rump/include/rump
cp ${RUMPSRC}/lib/librumpuser/rumpuser_component.h rump/include/rump

${MAKE} OS=${OS} -C libc

mkdir -p obj/lib/librumpuser

# We don't yet have enough to be able to run configure, coming soon
cp rumpuser_config.h ${RUMPSRC}/lib/librumpuser/

( export CPPFLAGS="-DRUMPUSER_CONFIG=yes -nostdinc -I${PWD}/libc/include -I${PWD}/rump/include -I${PWD}/src/sys/rump/include" && \
	cd ${RUMPSRC}/lib/librumpuser && \
	${RUMPMAKE} RUMPUSER_THREADS=fiber
	${RUMPMAKE} RUMPUSER_THREADS=fiber install )

LIBS="$(stdlibs ${RUMPSRC})"
if [ "$(${RUMPMAKE} -f rumptools/mk.conf -V '${_BUILDRUMP_CXX}')" = 'yes' ]
then
	LIBS="${LIBS} $(stdlibsxx ${RUMPSRC})"
fi

usermtree rump
userincludes ${RUMPSRC} ${LIBS}

for lib in ${LIBS}; do
	makeuserlib ${lib}
done

# tests

RUMPLIBS="-lrumpvfs -lrumpfs_kernfs -lrumpfs_ffs -lrumpdev_disk -lrumpdev -lrumpdev_rnd -lrumpnet -lrumpnet_net -lrumpnet_netinet -lrumpnet_netinet6 -lrump -lrumpuser"

mkdir -p obj/test bin
${CC} -nostdinc -I rump/include -c test/hello.c -o obj/test/hello.o
${CC} -nostdinc -nostdlib -Llib lib/crt1.o lib/crti.o obj/test/hello.o -Lrump/lib -lc -Wl,--whole-archive ${RUMPLIBS} -Wl,--no-whole-archive -lfranken lib/crtn.o -o bin/test

export RUMP_VERBOSE=1

./bin/test
