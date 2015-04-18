#!/bin/sh

# XXX should call compiler to find paths so works with 32 bit etc

cp /usr/lib/crti.o $1
cp /usr/lib/crtn.o $1
cp /usr/lib/crtbegin.o $1
cp /usr/lib/crtbeginT.o $1
cp /usr/lib/crtend.o $1
chmod u+w $1/crt*.o

# XXX also libgcc
