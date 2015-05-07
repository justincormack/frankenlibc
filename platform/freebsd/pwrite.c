#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include "init.h"

ssize_t __pwrite(int, const void *, size_t, off_t);

ssize_t
pwrite(int fd, const void *buf, size_t count, off_t offset)
{

	/* NetBSD writes some data to read only block devices */
	if ((__franken_fd[fd].flags & O_ACCMODE) != O_RDONLY)
		return __pwrite(fd, buf, count, offset);

	return EBADF;
}
