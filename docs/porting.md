## Porting

Currently most of the backends are userspace ports, but there is a bare
metal port and other ports are possible.

The libc converts to a very limited set of backend "system calls" that can
be implemented on any platform in order to run applications. These are as
follows, subject to minor change. The system calls mainly use the NetBSD ABI,
except for one, and the implementation should convert to whatever it needs.
There is very little to implement so this should not be onerous.

NetBSD ABI:
* clock\_gettime(CLOCK\_{REALTIME,MONOTONIC}, ...) clocks
* clock\_getres(CLOCK\_{REALTIME,MONOTONIC}, ...) clock resolution
* clock\_nanosleep(CLOCK\_MONOTONIC, 0, ...) sleep
* mmap() map anonymous memory (page allocator)
* munmap() unmap anonymous memory
* mprotect() change memory permissions
* kill(0, SIGABRT) abort program

Common ABI:
* \_exit(...) normal exit
* fstat() test if files exist
* write(1, ...) write to stdout.
* read(...) future use, read from console, virtual drivers
* pread, pwrite, fsync write to virtual block devices
* getpagesize() return the page size.

Linux ABI:
* getrandom() get random numbers to buffer. May fail or return short reads.
No flags supported.

Of these calls, only mmap, munmap and mprotect are exposed to the NetBSD libc, so the
rest do not need to worry what error codes they use. In addition the platform
needs some startup code, which should initialize argc, argv, and environ
with something suitable. The idea is that it should be very easy
to implement these calls on any platform with only a few lines of code, even
less than building a hypercall interface from scratch, at which point you can
support a full application stack on the rump kernel.
