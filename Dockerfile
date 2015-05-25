FROM ubuntu:15.04

MAINTAINER Justin Cormack

RUN apt-get update
RUN apt-get install -y build-essential libseccomp2 libseccomp-dev

COPY . /usr/src/frankenlibc
WORKDIR /usr/src/frankenlibc

RUN ./build.sh seccomp
