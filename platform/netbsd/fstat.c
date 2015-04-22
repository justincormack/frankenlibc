#include <sys/stat.h>
#include <errno.h>

#include "netbsd.h"

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

	st->st_mode = nst.st_mode;

	return 0;
}
