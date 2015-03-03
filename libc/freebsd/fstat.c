#include <sys/stat.h>
#include <errno.h>

#include "freebsd.h"

int __fstat(int, struct freebsd_stat *);

int
fstat(int fd, struct stat *st)
{
	int ret;
	struct freebsd_stat fst;

	ret = __fstat(fd, &fst);
	if (ret == -1) {
		errno = EBADF;
		return -1;
	}

	st->st_size = fst.st_size;
	st->st_mode = (FREEBSD_S_ISDIR (fst.st_mode) ? S_IFDIR  : 0) |
		      (FREEBSD_S_ISCHR (fst.st_mode) ? S_IFCHR  : 0) |
		      (FREEBSD_S_ISBLK (fst.st_mode) ? S_IFBLK  : 0) |
		      (FREEBSD_S_ISREG (fst.st_mode) ? S_IFREG  : 0) |
		      (FREEBSD_S_ISFIFO(fst.st_mode) ? S_IFIFO  : 0) |
		      (FREEBSD_S_ISLNK (fst.st_mode) ? S_IFLNK  : 0) |
		      (FREEBSD_S_ISSOCK(fst.st_mode) ? S_IFSOCK : 0);

	return 0;
}
