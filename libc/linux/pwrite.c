#include <unistd.h>
#include <errno.h>

#include "linux.h"

#ifdef _LP64
ssize_t __pwrite(int, const void *, size_t, off_t);

ssize_t
pwrite(int fd, const void *buf, size_t count, off_t offset)
{

	return __pwrite(fd, buf, count, offset);
}
#else
#define __SYSCALL_LL_E(x) \
((union { long long ll; long l[2]; }){ .ll = x }).l[0], \
((union { long long ll; long l[2]; }){ .ll = x }).l[1]

#ifdef SYSCALL_ZEROPAD
ssize_t __pwrite(int, const void *, size_t, int, long, long);

ssize_t
pwrite(int fd, const void *buf, size_t count, off_t offset)
{

	return __pwrite(fd, buf, count, 0, __SYSCALL_LL_E(offset));
}
#else
ssize_t __pwrite(int, const void *, size_t, long, long);

pwrite(int fd, const void *buf, size_t count, off_t offset)
{

	return __pwrite(fd, buf, count, __SYSCALL_LL_E(offset));
}
#endif
#endif
