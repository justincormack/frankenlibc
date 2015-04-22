#include <unistd.h>
#include <errno.h>

#include "syscall.h"
#include "linux.h"

ssize_t
read(int fd, void *buf, size_t count)
{
	int ret;

	ret = syscall(SYS_read, fd, buf, count);

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
