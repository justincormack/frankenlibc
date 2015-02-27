### Frankenlibc ###

Frankenlibc is an experimental build tool to make writing applications
against rump kernels easier, and to unify code.

There are known and unknown bugs!

[![Build Status](https://travis-ci.org/justincormack/frankenlibc.png?branch=master)](https://travis-ci.org/justincormack/frankenlibc)

build with "make", or with "./buildc.sh" for additional options.

It is a small C library that serves several functions, that should perhaps
be isolated better.

1. It provides enough of a libc to compile the fiber-based librumpuser
implementation that is upstream in NetBSD (modulo some temporary patches
that are not upstreamed yet).
2. It provides some stubs that the built for rump NetBSD libc is missing,
some of which overlap with 1, like malloc, free, others of which do nothing.
3. It will provide the pthread backend implementation that is working on
rumprun-posix, xen etc, not transferred over yet.

The libc functions are namespaced to make sure they do not conflict with
functions in a NetBSD libc linked to the application.

The libc converts to a very limited set of backend "system calls" that can
be implemented on any platform in order to run applications. These are as
follows, subject to minor change. The system calls mainly use the NetBSD ABI,
except for one, and the implementation should convert to whatever it needs.
There is very little to implement so this should not be onerous.

NetBSD ABI:
* clock\_gettime(CLOCK\_{REALTIME,MONOTONIC}, ...) clocks
* clock\_nanosleep(CLOCK\_MONOTONIC, 0, ...) sleep
* mmap() map anonymous memory (page allocator)
* munmap() unmap anonymous memory
* mprotect() change memory permissions
* kill(0, SIGABRT) abort program

Common ABI:
* \_exit(...) normal exit
* write(1, ...) write to stdout.
* isatty(1) is stdout a tty?
* getpagesize() return the page size.

Linux ABI:
* getrandom() get random numbers to buffer. May fail or return short reads.
No flags supported.

Of these calls, only mmap, munmap and mprotect are exposed to the NetBSD libc, so the
rest do not need to worry what error codes they use. In addition the platform
needs some startup code, which should initialize argc, argv, environ and
\_\_progname with something suitable. The idea is that it should be very easy
to implement these calls on any platform with only a few lines of code, even
less than building a hypercall interface from scratch, at which point you can
support a full application stack on the rump kernel.

Currently there are two implementations included, NetBSD x86\_64 and Linux
x86\_64. These have a few features missing but work ok.
