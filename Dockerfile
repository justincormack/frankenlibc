# Basic build of frankenlibc with Docker

FROM alpine:3.2

MAINTAINER Justin Cormack <justin@specialbusservice.com>

RUN \
  apk update && \
  apk upgrade && \
  apk add \
  build-base \
  linux-headers \
  gawk \
  sed \
  zlib-dev \
  openssl-dev \
  ncurses-dev \
  file \
  wget \
  git \
  rsync \
  m4 \
  strace \
  cdrkit \
  coreutils \
  bash \
  dnsmasq \
  iproute2 \
  bridge-utils \
  ethtool \
  cmake \
  curl

# While still in testing
RUN \
  apk -X http://nl.alpinelinux.org/alpine/edge/testing update && \
  apk -X http://nl.alpinelinux.org/alpine/edge/testing add libseccomp libseccomp-dev

COPY . /usr/src/frankenlibc

ENV SUDO_UID=1000

RUN \
  cd /usr/src/frankenlibc && \
  LDSTATIC=-static ./build.sh -F CPPFLAGS=-U_FORTIFY_SOURCE -d /usr/local/rump -b /usr/local/bin seccomp && \
  cp rumpobj/tests/hello /usr/local/bin/rump.helloworld && \
  make clean
