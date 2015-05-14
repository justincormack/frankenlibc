#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include "syscall.h"
#include "init.h"

ssize_t
pwrite(int fd, const void *buf, size_t count, off_t offset)
{

	/* NetBSD writes some data to read only block devices */
	if ((__franken_fd[fd].flags & O_ACCMODE) == O_RDONLY)
		return EBADF;

	return syscall(SYS_pwrite, fd, buf, count, __SYSCALL_LL_O(offset));
}
