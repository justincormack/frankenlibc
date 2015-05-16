#if defined(__x86_64__)
#include "x86_64/syscall.h"
#elif defined(__i386__)
#include "i386/syscall.h"
#elif defined(__ARMEL__) || defined(__ARMEB__)
#include "arm/syscall.h"
#elif defined(__AARCH64EL__) || defined (__AARCH64EB__)
#include "aarch64/syscall.h"
#elif defined(__PPC64__)
#include "ppc64/syscall.h"
#elif defined(__PPC__)
#include "ppc/syscall.h"
#else
#error "Unknown architecture"
#endif

#define SYS_read                        3
#define SYS_write                       4
#define SYS___fstat50                   440
#define SYS_mmap                        197
#define SYS_munmap                      73
#define SYS_ioctl                       54
#define SYS_kill                        37
#define SYS_mprotect                    74
#define SYS_fcntl                       92
#define SYS_fsync                       95
#define SYS_readv                       120
#define SYS_writev                      121
#define SYS_pread                       173
#define SYS_pwrite                      174
#define SYS_preadv                      289
#define SYS_pwritev                     290
#define SYS___clock_gettime50           427
#define SYS___clock_getres50            429
#define SYS_clock_nanosleep             477
#define SYS_exit                        1
#define SYS___sysctl                    202
#define SYS___nanosleep50               430
#define SYS___pollts50                  437

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
