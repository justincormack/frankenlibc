# Basic build of frankenlibc with Docker

FROM ubuntu:15.04

MAINTAINER Justin Cormack

RUN apt-get update && apt-get install -y \
  binutils \
  cpp \
  gcc \
  git \
  libc6-dev \
  libseccomp2 \
  libseccomp-dev \
  make

COPY . /usr/src/frankenlibc

RUN cd /usr/src/frankenlibc && ./build.sh -d /usr/local seccomp notests && /usr/local/bin/rumprun-cc -g -O2 tests/hello.c -o /usr/local/bin/rump.helloworld && make clean
