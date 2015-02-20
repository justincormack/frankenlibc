#!/bin/sh

# nothing else supported yet
OS=linux
ARCH=x86_64

RUMPSRC=rumpsrc

[ ! -f ./buildrump.sh/subr.sh ] && git submodule update --init buildrump.sh
( [ ! -f rumpsrc/build.sh ] && git submodule update --init rumpsrc \
	&& cd rumpsrc && cat ../rumpuser.patch | patch -p1 )

set -e

. ./buildrump.sh/subr.sh

./buildrump.sh/buildrump.sh \
	-V RUMP_CURLWP=hypercall -V MKPIC=no -V RUMP_KERNEL_IS_LIBC=1 \
	-F CFLAGS=-fno-stack-protector \
	-k -N -s ${RUMPSRC} \
	tools build kernelheaders install

RUMPMAKE=${PWD}/obj/tooldir/rumpmake

# -k build does not install rumpuser headers
mkdir -p rump/include/rump
cp ${RUMPSRC}/lib/librumpuser/rumpuser_component.h rump/include/rump

MAKE=${MAKE-make}
CC=${CC-cc}
AR=${AR-ar}
OBJCOPY=${OBJCOPY-objcopy}

${MAKE} -C libc

mkdir -p obj/lib/librumpuser

# We don't yet have enough to be able to run configure, coming soon
cp rumpuser_config.h ${RUMPSRC}/lib/librumpuser/

( export CPPFLAGS="-DRUMPUSER_CONFIG=yes -nostdinc -I${PWD}/libc/include -I${PWD}/rump/include -I${PWD}/src/sys/rump/include" && \
	cd ${RUMPSRC}/lib/librumpuser && \
	${RUMPMAKE} RUMPUSER_THREADS=fiber
	${RUMPMAKE} RUMPUSER_THREADS=fiber install )

# now combine our C library and librumpuser, with only needed symbols exposed
# may be a better way of doing this
${CC} -Wl,-r -nostdlib obj/lib/librumpuser/*.o obj/libc/*.o -o obj/join.o
${OBJCOPY} -w --localize-symbol='*' obj/join.o
for s in calloc errno __errno _exit free malloc _lwp_kill _lwp_self mmap _mmap munmap __platform_init posix_memalign realloc __sigaction_sigtramp __sigprocmask14
do
	${OBJCOPY} --globalize-symbol=${s} obj/join.o
done
${OBJCOPY} -w --globalize-symbol='rumpuser*' obj/join.o
rm -f rump/lib/librumpuser.a
${AR} cr rump/lib/librumpuser.a obj/join.o 

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

mkdir -p obj/test bin
${CC} -nostdinc -I rump/include -c test/hello.c -o obj/test/hello.o
${CC} -nostdlib lib/crt1.o lib/crti.o obj/test/hello.o rump/lib/libc.a -Wl,--no-as-needed rump/lib/librump.a rump/lib/librumpuser.a -Wl,--as-needed lib/libc.a lib/crtn.o -o bin/test

./bin/test
