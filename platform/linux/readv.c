#include <sys/uio.h>
#include <errno.h>

#include "syscall.h"
#include "linux.h"

ssize_t
readv(int fd, const struct iovec *iov, int iovcnt)
{
	int ret;

	ret = syscall(SYS_readv, fd, iov, iovcnt);

	if (ret == -1) {
		switch (errno) {
		case LINUX_EAGAIN:
			errno = EAGAIN;
			break;
		default:
			errno = EBADF;
			break;
		}
	}

	return ret;
}
