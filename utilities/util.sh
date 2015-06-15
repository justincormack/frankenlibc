#!/bin/sh

mkdir -p ${OBJDIR}/$1
cd $2
${RUMPMAKE} clean
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
	${RUMPMAKE} CC="${CC}" MAKEOBJDIR=${OBJDIR}/$1
cp ${OBJDIR}/$1/$1 $3
