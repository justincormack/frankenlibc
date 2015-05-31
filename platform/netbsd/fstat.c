#include <sys/stat.h>
#include <errno.h>

#include "netbsd.h"
#include "init.h"

int __ioctl(int, unsigned long, ...);
int __fstat(int, struct netbsd_stat *);

int
fstat(int fd, struct stat *st)
{
	int ret;
	struct netbsd_stat nst;

	ret = __fstat(fd, &nst);
	if (ret == -1) {
		return -1;
	}

	st->st_size = nst.st_size;

	if (S_ISBLK(nst.st_mode)) {
		/* XXX block device size is messy in NetBSD, work out */
	}
	if (S_ISREG(nst.st_mode) && (fd == 3 || __franken_fd[fd].mounted == 1)) {
		nst.st_mode &= ~S_IFMT;
		nst.st_mode |= S_IFBLK;
	}

	st->st_mode = nst.st_mode;

	return 0;
}
