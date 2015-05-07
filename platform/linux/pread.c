#include <unistd.h>

#include "syscall.h"

ssize_t
pread(int fd, void *buf, size_t count, off_t offset)
{

	return syscall(SYS_pread, fd, buf, count, __SYSCALL_LL_O(offset));
}
