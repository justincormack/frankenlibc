#include <sys/uio.h>
#include <errno.h>

#include "syscall.h"
#include "linux.h"

ssize_t
pwritev(int fd, const struct iovec *iov, int iovcnt, off_t off)
{
	int ret;

	ret = syscall(SYS_pwritev, fd, iov, iovcnt, (long)(off), (long)(off>>32));

	if (ret == -1) {
		switch (errno) {
		case LINUX_EAGAIN:
			errno = EAGAIN;
			break;
		case LINUX_ESPIPE:
			errno = ESPIPE;
		default:
			errno = EBADF;
			break;
		}
	}

	return ret;
}
