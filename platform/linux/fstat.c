#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#include "syscall.h"
#include "linux.h"
#include "init.h"

int __platform_random_fd = -1;
int __platform_socket_fd = -1;
int __platform_npoll = 0;
struct pollfd __platform_pollfd[MAXFD];

int
fstat(int fd, struct stat *st)
{
	int ret;
	struct linux_stat lst;
	struct ifreq ifr;

	ret = syscall(SYS_fstat, fd, &lst);
	if (ret == -1) {
		errno = EBADF;
		return -1;
	}

	st->st_size = lst.st_size;

	switch (lst.st_mode & LINUX_S_IFMT) {
	case LINUX_S_IFSOCK:
		__platform_socket_fd = fd;
		/* currently no support for raw socket networking */
		lst.st_mode = 0;
		break;
	case LINUX_S_IFBLK:
		syscall(SYS_ioctl, fd, BLKGETSIZE64, &st->st_size);
		break;
	case LINUX_S_IFCHR:
		/* test if /dev/net/tun or macvtap */
		if (!(lst.st_rdev == makedev(10, 200) || major(lst.st_rdev) == 246))
			break;
		ret = syscall(SYS_ioctl, fd, TUNGETIFF, &ifr);
		if (ret == 0) {
			/* we do not yet support macvtap offload facilities */
			if (ifr.ifr_flags & IFF_VNET_HDR) {
				ifr.ifr_flags &= ~IFF_VNET_HDR;
				syscall(SYS_ioctl, fd, TUNSETIFF, &ifr);
			}
			/* use sock type to tell config we are network */
			lst.st_mode = LINUX_S_IFSOCK;
			/* find mac address */
			ret = syscall(SYS_ioctl, fd, SIOCGIFHWADDR, &ifr);
			if (ret == -1 && __platform_socket_fd != -1)
				ret = syscall(SYS_ioctl, __platform_socket_fd, SIOCGIFHWADDR, &ifr);
			if (ret == 0) {
				memcpy(st->st_hwaddr, ifr.ifr_addr.sa_data, 6);
			}
			__platform_pollfd[__platform_npoll].fd = fd;
			__platform_pollfd[__platform_npoll].events = POLLIN | POLLPRI;
			__platform_npoll++;
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

	/* if we are passed in /dev/urandom use as a random source */
	if (LINUX_S_ISCHR(lst.st_mode) && lst.st_rdev == makedev(1, 9))
		__platform_random_fd = fd;

	return 0;
}
