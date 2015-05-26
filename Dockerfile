# Basic build of frankenlibc with Docker

FROM ubuntu:15.04

MAINTAINER Justin Cormack

RUN apt-get update && apt-get install -y \
  binutils \
  cpp \
  curl \
  g++ \
  gcc \
  git \
  libc6-dev \
  libseccomp2 \
  libseccomp-dev \
  make

COPY . /usr/src/frankenlibc

RUN \
  cd /usr/src/frankenlibc && \
  ./build.sh -d /usr/local/rump -b /usr/local/bin seccomp notests && \
  rumprun-cc -g -O2 tests/hello.c -o /usr/local/bin/rump.helloworld && \
  make clean
