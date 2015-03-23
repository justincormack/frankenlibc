#include <unistd.h>
#include <errno.h>

#include "syscall.h"

ssize_t
pwrite(int fd, const void *buf, size_t count, off_t offset)
{

	return syscall(SYS_pwrite, fd, buf, count, __SYSCALL_LL_O(offset));
}
