#include <sys/stat.h>
#include <errno.h>

#include "linux.h"

int __platform_random_fd = -1;

int __fstat(int, struct linux_stat *);

int
fstat(int fd, struct stat *st)
{
	int ret;
	struct linux_stat lst;

	ret = __fstat(fd, &lst);
	if (ret == -1) {
		errno = EBADF;
		return -1;
	}

	st->st_size = lst.st_size;
	st->st_mode = (LINUX_S_ISDIR (lst.st_mode) ? S_IFDIR  : 0) |
		      (LINUX_S_ISCHR (lst.st_mode) ? S_IFCHR  : 0) |
		      (LINUX_S_ISBLK (lst.st_mode) ? S_IFBLK  : 0) |
		      (LINUX_S_ISREG (lst.st_mode) ? S_IFREG  : 0) |
		      (LINUX_S_ISFIFO(lst.st_mode) ? S_IFIFO  : 0) |
		      (LINUX_S_ISLNK (lst.st_mode) ? S_IFLNK  : 0) |
		      (LINUX_S_ISSOCK(lst.st_mode) ? S_IFSOCK : 0);

	/* if we are passed in /dev/urandom use as a random source */
	if (LINUX_S_ISCHR(lst.st_mode) && lst.st_rdev == linux_makedev(1, 9))
		__platform_random_fd = fd;

	return 0;
}
