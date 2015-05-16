#include "syscall.h"

SYSCALL(clock_nanosleep, __clock_nanosleep);
SYSCALL(__fstat50, __fstat);
SYSCALL(exit, _exit);
SYSCALL(__clock_getres50, __platform_clock_getres);
SYSCALL(__clock_gettime50, __platform_clock_gettime);
SYSCALL(fcntl, __platform_fcntl);
SYSCALL(fsync, __platform_fsync);
SYSCALL(ioctl, __ioctl);
SYSCALL(kill, __platform_kill);
#ifdef SYSCALL6
SYSCALL6(mmap, __platform_mmap);
#else
SYSCALL(mmap, __platform_mmap);
#endif
SYSCALL(mprotect, mprotect);
SYSCALL(munmap, munmap);
SYSCALL(__nanosleep50, __platform_nanosleep);
SYSCALL(pread, __platform_pread);
SYSCALL(preadv, __platform_preadv);
SYSCALL(pwrite, __platform_pwrite);
SYSCALL(pwritev, __platform_pwritev);
SYSCALL(read, __platform_read);
SYSCALL(readv, __platform_readv);
SYSCALL(__sysctl, __platform_sysctl);
SYSCALL(write, __platform_write);
SYSCALL(writev, __platform_writev);
