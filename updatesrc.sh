#!/bin/sh

NBCVS=anoncvs@anoncvs.NetBSD.org:/cvsroot

rm -rf src
cvs -d ${NBCVS} co -P src/sys/rump/listsrcdirs
cvs -d ${NBCVS} co -P src/build.sh
cvs -d ${NBCVS} co -P src/Makefile
cvs -d ${NBCVS} co -P src/Makefile.inc
sh ./src/sys/rump/listsrcdirs -c all | xargs cvs -d ${NBCVS} -z3 co -P
git add -A src
git status
