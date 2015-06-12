# Basic build of frankenlibc with Docker

FROM ubuntu:15.04

MAINTAINER Justin Cormack <justin@specialbusservice.com>

RUN apt-get update && apt-get install -y \
  binutils \
  cpp \
  curl \
  g++ \
  gcc \
  git \
  libc6-dev \
  libcap2 \
  libcap-dev \
  libseccomp2 \
  libseccomp-dev \
  strace \
  make

COPY . /usr/src/frankenlibc

ENV SUDO_UID=1000

RUN \
  cd /usr/src/frankenlibc && \
  ./build.sh -d /usr/local/rump -b /usr/local/bin seccomp && \
  cp rumpobj/tests/hello /usr/local/bin/rump.helloworld && \
  make clean
