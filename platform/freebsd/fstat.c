#include <sys/stat.h>
#include <errno.h>

#include "freebsd.h"
#include "init.h"

int __ioctl(int, unsigned long, ...);
int __fstat(int, struct freebsd_stat *);

int __platform_npoll = 0;
struct pollfd __platform_pollfd[MAXFD];

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

	switch (fst.st_mode & FREEBSD_S_IFMT) {
	case FREEBSD_S_IFBLK:
		__ioctl(fd, DIOCGMEDIASIZE, &fst.st_size);
		break;
	case FREEBSD_S_IFCHR:
		/* XXX only for tap device */
		ret = __ioctl(fd, SIOCGIFADDR, st->st_hwaddr);
		if (ret == 0) {
			/* say we are a "socket" ie network device */
			fst.st_mode = FREEBSD_S_IFSOCK;
			/* add to poll */
			__platform_pollfd[__platform_npoll].fd = fd;
			__platform_pollfd[__platform_npoll].events = POLLIN | POLLPRI;
			__platform_npoll++;
		}
		break;
	}

	st->st_mode = (FREEBSD_S_ISDIR (fst.st_mode) ? S_IFDIR  : 0) |
		      (FREEBSD_S_ISCHR (fst.st_mode) ? S_IFCHR  : 0) |
		      (FREEBSD_S_ISBLK (fst.st_mode) ? S_IFBLK  : 0) |
		      (FREEBSD_S_ISREG (fst.st_mode) ? S_IFREG  : 0) |
		      (FREEBSD_S_ISFIFO(fst.st_mode) ? S_IFIFO  : 0) |
		      (FREEBSD_S_ISLNK (fst.st_mode) ? S_IFLNK  : 0) |
		      (FREEBSD_S_ISSOCK(fst.st_mode) ? S_IFSOCK : 0);

	return 0;
}
