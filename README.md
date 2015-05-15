### Frankenlibc ###

Frankenlibc is an experimental build tool to make writing applications
against rump kernels easier, and to unify code.

There are known and unknown bugs!

[![Build Status](https://travis-ci.org/justincormack/frankenlibc.png?branch=master)](https://travis-ci.org/justincormack/frankenlibc)

build with "make", or with "./build.sh" for additional options.

Frankenlibc provides a small libc that is enough to let the fiber-based librumpuser
library run natively on your platform without any system libraries. It
combines this library, the rump kernel, and NetBSD's libc into a single
libc that you can just use to link against applications to make them run
against a rump kernel rather than the host.

Currently there are three userspace implementations included, NetBSD, Linux and FreeBSD,
and one very basic baremetal implementation, qemu-arm. The supported architectures
are x86\_64, i386, arm, powerpc, powerpc64 and mips, with work in progress support for aarch64. Both arm
and mips work with hard and soft float. Powerpc supports the v1 ELF ABI only at present. Not all
the architectures work on all the platforms
yet but the work to port them is minimal. Additional implementations and architectures
will be added soon.

There is also an option to build a deterministic version with no random numbers and a fake
clock, so runs are completely repeatable.

There is a wrapper called rexec ("rump exec") that can pass in files, block devices
and tap devices as network devices, and will also run the program in a seccomp
sandbox on Linux or under Capsicum on FreeBSD. These are pretty aggressive, eg
open cannot be called, but you may want to add further sandboxing in addition.

A compiler wrapper is generated in rump/bin to compile your own programs, which works out
the best method to wrap the compiler. Essentially you just need to use the include files,
libc and other libraries and crt files in the rump/ output directory. For gcc a spec file
is used, while many clang installations can use a sysroot, although eg NetBSD's linker
does not support sysroot. For most systems a line like the following will work if you
do not use the wrapper:

gcc -nostdinc -Irump/include -Lrump/lib -Brump/lib -o rumpobj/tests/hello -static tests/hello.c
