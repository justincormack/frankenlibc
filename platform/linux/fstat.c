#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#include "syscall.h"
#include "linux.h"
#include "init.h"

extern int __platform_socket_fd;

int
fstat(int fd, struct stat *st)
{
	int ret;
	struct linux_stat lst;
	struct ifreq ifr = {0};
	struct sockaddr_ll sa;
	int slen = sizeof(sa);

	ret = syscall(SYS_fstat, fd, &lst);
	if (ret == -1) {
		errno = EBADF;
		return -1;
	}

	st->st_size = lst.st_size;

	switch (lst.st_mode & LINUX_S_IFMT) {
	case LINUX_S_IFSOCK:
		/* is this a raw socket? */
		ret = syscall(SYS_getsockname, fd, &sa, &slen);
		if (ret == 0 && sa.sll_family == AF_PACKET) {
			ifr.ifr_ifindex = sa.sll_ifindex;
			ret = syscall(SYS_ioctl, fd, SIOCGIFNAME, &ifr);
			ret = syscall(SYS_ioctl, fd, SIOCGIFHWADDR, &ifr);
			if (ret == 0) {
				memcpy(st->st_hwaddr, ifr.ifr_addr.sa_data, 6);
			}
			/* XXX need IP address */
		} else {
			lst.st_mode = 0;
		}
		break;
	case LINUX_S_IFBLK:
		syscall(SYS_ioctl, fd, BLKGETSIZE64, &st->st_size);
		break;
	case LINUX_S_IFCHR:
		/* macvtap has a dynamic major number, so hard to test */
		if (lst.st_rdev != makedev(10, 200) && major(lst.st_rdev) < 138)
			break;
		ret = syscall(SYS_ioctl, fd, TUNGETIFF, &ifr);
		if (ret == 0) {
			/* use sock type to tell config we are network */
			lst.st_mode = LINUX_S_IFSOCK;
			/* find mac address */
			ret = syscall(SYS_ioctl, fd, SIOCGIFHWADDR, &ifr);
			if (ret == -1 && __platform_socket_fd != -1)
				ret = syscall(SYS_ioctl, __platform_socket_fd, SIOCGIFHWADDR, &ifr);
			if (ret == 0) {
				memcpy(st->st_hwaddr, ifr.ifr_addr.sa_data, 6);
			}
		}
		break;
	case LINUX_S_IFREG:
		/* pretend it is a block device */
		if (fd == 3 || __franken_fd[fd].mounted == 1) {
			lst.st_mode &= ~LINUX_S_IFMT;
			lst.st_mode |= LINUX_S_IFBLK;
		}
		break;
	}

	st->st_mode = (LINUX_S_ISDIR (lst.st_mode) ? S_IFDIR  : 0) |
		      (LINUX_S_ISCHR (lst.st_mode) ? S_IFCHR  : 0) |
		      (LINUX_S_ISBLK (lst.st_mode) ? S_IFBLK  : 0) |
		      (LINUX_S_ISREG (lst.st_mode) ? S_IFREG  : 0) |
		      (LINUX_S_ISFIFO(lst.st_mode) ? S_IFIFO  : 0) |
		      (LINUX_S_ISLNK (lst.st_mode) ? S_IFLNK  : 0) |
		      (LINUX_S_ISSOCK(lst.st_mode) ? S_IFSOCK : 0);

	return 0;
}
