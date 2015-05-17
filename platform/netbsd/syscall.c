#include "syscall.h"

#include <sys/types.h>

/* some architecture eg Arm use _syscall() instead */

#ifdef SYSCALL
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
#else
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <time.h>
#include <fcntl.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <sys/uio.h>
long _syscall(int, ...);
int __fstat(int fd, struct stat *st) {return _syscall(SYS___fstat50, fd, st);}
int fsync(int fd) {return _syscall(SYS_fsync, fd);}
void _exit(int status) {_syscall(SYS_exit, status);}
ssize_t preadv(int fd, const struct iovec *iov, int count, off_t offset) {return _syscall(SYS_preadv, fd, iov, count, offset);}
ssize_t pwritev(int fd, const struct iovec *iov, int count, off_t offset) {return _syscall(SYS_pwritev, fd, iov, count, offset);}
ssize_t readv(int fd, const struct iovec *iov, int count) {return _syscall(SYS_readv, fd, iov, count);}
ssize_t writev(int fd, const struct iovec *iov, int count) {return _syscall(SYS_writev, fd, iov, count);}
ssize_t pread(int fd, void *buf, size_t count, off_t offset) {return _syscall(SYS_pread, fd, buf, count, offset);}
ssize_t pwrite(int fd, const void *buf, size_t count, off_t offset) {return _syscall(SYS_pwrite, fd, buf, count, offset);}
ssize_t read(int fd, void *buf, size_t count) {return _syscall(SYS_read, fd, buf, count);}
ssize_t write(int fd, const void *buf, size_t count) {return _syscall(SYS_write, fd, buf, count);}
int kill(pid_t pid, int sig) {return _syscall(SYS_kill, pid, sig);}
void *mmap(void *mem, size_t length, int prot, int flags, int fd, off_t offset) {return (void *)_syscall(SYS_mmap, mem, length, prot, flags, fd, offset);}
int munmap(void *mem, size_t size) {return _syscall(SYS_munmap, mem, size);}
int mprotect(void *mem, size_t size, int prot) {return _syscall(SYS_mprotect, mem, size, prot);}
int clock_getres(clockid_t id, struct timespec *ts) {return _syscall(SYS___clock_getres50, id, ts);}
int clock_gettime(clockid_t id, struct timespec *ts) {return _syscall(SYS___clock_gettime50, id, ts);}
int __platform_nanosleep(const struct timespec *req, struct timespec *rem) {return _syscall(SYS___nanosleep50, req, rem);}
int __clock_nanosleep(clockid_t id, int flags, const struct timespec *req, struct timespec *rem) {return _syscall(SYS_clock_nanosleep, id, flags, req, rem);}
int fcntl(int fd, int cmd, ...)
{
	unsigned long arg;
	va_list ap;

	va_start(ap, cmd);
	arg = va_arg(ap, unsigned long);
	va_end(ap);

	return _syscall(SYS_fcntl, fd, cmd, arg);
}
/* XXX add headers */
int __platform_sysctl(const int *a, unsigned int b, void *c, size_t *d, const void *e, size_t f) {return _syscall(SYS___sysctl, a, b, c, d, e, f);}
int __platform_ioctl(int fd, unsigned long cmd, ...)
{
	unsigned long arg;
	va_list ap;

	va_start(ap, cmd);
	arg = va_arg(ap, unsigned long);
	va_end(ap);

	return _syscall(SYS_ioctl, fd, cmd, arg);
}
#endif
