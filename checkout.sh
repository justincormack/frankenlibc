#!/bin/sh

SRC=src

[ ! -z $1 ] && SRC=$1

NBCVS=anoncvs@anoncvs.NetBSD.org:/cvsroot

TMPDIR=$(mktemp -d tmp.XXXX)

mkdir -p ${TMPDIR}
cd ${TMPDIR}

cvs -d ${NBCVS} co -P src/sys/rump/listsrcdirs
cvs -d ${NBCVS} co -P src/build.sh
cvs -d ${NBCVS} co -P src/Makefile
cvs -d ${NBCVS} co -P src/Makefile.inc
sh src/sys/rump/listsrcdirs -c all | xargs cvs -d ${NBCVS} -z3 co -P

cd -

rm -rf ${SRC}
mkdir -p ${SRC}
mv ${TMPDIR}/src/* ${SRC}
rm -rf ${TMPDIR}
