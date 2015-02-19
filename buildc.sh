#!/bin/sh

set -x

# nothing else supported yet
OS=linux
ARCH=x86_64

RUMPSRC=rumpsrc

[ ! -f ./buildrump.sh/subr.sh ] && git submodule update --init buildrump.sh
( [ ! -f rumpsrc/build.sh ] && git submodule update --init rumpsrc \
	&& cd rumpsrc && cat ../rumpuser.patch | patch -p1 )

. ./buildrump.sh/subr.sh

./buildrump.sh/buildrump.sh \
	-V RUMP_CURLWP=hypercall -V MKPIC=no -V RUMP_KERNEL_IS_LIBC=1 \
	-F CFLAGS=-fno-stack-protector -k -s ${RUMPSRC} \
	tools build kernelheaders install

RUMPMAKE=${PWD}/obj/tooldir/rumpmake

( cd libc && make )

ar cr lib/libc.a obj/libc/*.o

# -k build does not install rumpuser headers 
mkdir -p rump/include/rump
cp src/lib/librumpuser/rumpuser_component.h rump/include/rump

mkdir -p obj/lib/librumpuser

#export CPPFLAGS="-DRUMPUSER_CONFIG=yes -nostdinc -I${PWD}/include -I${PWD}/rump/include -I${PWD}/src/sys/rump/include"

# We don't yet have enough to be able to run configure, coming soon
cp rumpuser_config.h src/lib/librumpuser/

( CPPFLAGS="-DRUMPUSER_CONFIG=yes -nostdinc -I${PWD}/include -I${PWD}/rump/include -I${PWD}/src/sys/rump/include" \
	cd ${RUMPSRC}/lib/librumpuser && ${RUMPMAKE} RUMPUSER_THREADS=fiber )

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


