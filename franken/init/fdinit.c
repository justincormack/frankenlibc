#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>

#include "init.h"

enum rump_etfs_type {
	RUMP_ETFS_REG,
	RUMP_ETFS_BLK,
	RUMP_ETFS_CHR,
	RUMP_ETFS_DIR,
	RUMP_ETFS_DIR_SUBDIRS
};

int rump_pub_etfs_register(const char *, const char *, enum rump_etfs_type);
int rump_pub_netconfig_ifcreate(const char *) __attribute__ ((weak));
int rump_pub_netconfig_dhcp_ipv4_oneshot(const char *) __attribute__ ((weak));
int rump_pub_netconfig_ifcreate(const char *interface) {return 0;}
int rump_pub_netconfig_dhcp_ipv4_oneshot(const char *interface) {return 0;}

struct __fdtable __franken_fd[MAXFD];

/* XXX should have proper functions in libc */
void
mkkey(char *k, char *n, const char *pre, int fd)
{
	int i, d;

	if (fd > 99) abort();
	for (i = 0; i < strlen(pre); i++)
		*k++ = pre[i];
	if (fd > 9) {
		d = (fd / 10) + '0';
		*k++ = d;
		*n++ = d;
		fd /= 10;
	}
	d = fd + '0';
	*k++ = d;
	*k++ = 0;
	*n++ = d;
	*n++ = 0;
}

void
__franken_fdinit()
{
	int fd;
	struct stat st;
	char *mem;
	int ret;

	/* iterate over numbered descriptors, stopping when one does not exist */
	for (fd = 0; fd < MAXFD; fd++) {
		memset(&st, 0, sizeof(struct stat));
		if (fstat(fd, &st) == -1) {
			__franken_fd[fd].valid = 0;
			break;
		}
		__franken_fd[fd].valid = 1;
		__franken_fd[fd].flags = fcntl(fd, F_GETFL, 0);
		memcpy(&__franken_fd[fd].st, &st, sizeof(struct stat));
		switch (st.st_mode & S_IFMT) {
		case S_IFREG:
			__franken_fd[fd].seek = 1;
			mkkey(__franken_fd[fd].key, __franken_fd[fd].num, "/dev/fr", fd);
			break;
		case S_IFBLK:
			__franken_fd[fd].seek = 1;
			mkkey(__franken_fd[fd].key, __franken_fd[fd].num, "/dev/fr", fd);
			break;
		case S_IFCHR:
			/* XXX Linux presents stdin as char device see notes to clean up */
			__franken_fd[fd].seek = 0;
			mkkey(__franken_fd[fd].key, __franken_fd[fd].num, "/dev/fr", fd);
			break;
		case S_IFIFO:
			__franken_fd[fd].seek = 0;
			mkkey(__franken_fd[fd].key, __franken_fd[fd].num, "/dev/fr", fd);
			break;
		case S_IFSOCK:
			__franken_fd[fd].seek = 0;
			mkkey(__franken_fd[fd].key, __franken_fd[fd].num, "virt", fd);
			break;
		}
	}
}

/* XXX would be much nicer to build these functions against NetBSD libc headers, but at present
   they are not built, or installed, yet. Need to reorder the build process */

struct ufs_args {
	char *fspec;
};

#define MNT_RDONLY	0x00000001

int rump___sysimpl___sysctl(const int *, unsigned int, void *, size_t *, const void *, size_t);
#define CTL_NET         4
#define CTL_NET_INET6   24
#define IPV6CTL_ACCEPT_RTADV    12
int rump___sysimpl_open(const char *, int, ...);
int rump___sysimpl_close(int);
int rump___sysimpl_dup2(int, int);
int rump___sysimpl_mount50(const char *, const char *, int, void *, size_t);

void
__franken_fdinit_create()
{
	int fd, ret, flags;
	int root = 0;

	if (__franken_fd[0].valid) {
		rump_pub_etfs_register(__franken_fd[0].key, __franken_fd[0].num, RUMP_ETFS_REG);
		fd = rump___sysimpl_open(__franken_fd[0].key, O_RDONLY);
		if (fd != -1) {
			rump___sysimpl_dup2(fd, 0);
			rump___sysimpl_close(fd);
		}
	}
	if (__franken_fd[1].valid) {
		rump_pub_etfs_register(__franken_fd[1].key, __franken_fd[1].num, RUMP_ETFS_REG);
		fd = rump___sysimpl_open(__franken_fd[1].key, O_WRONLY);
		if (fd != -1) {
			rump___sysimpl_dup2(fd, 1);
			rump___sysimpl_close(fd);
		}
	}

	if (__franken_fd[2].valid) {
		rump_pub_etfs_register(__franken_fd[2].key, __franken_fd[2].num, RUMP_ETFS_REG);
		fd = rump___sysimpl_open(__franken_fd[2].key, O_WRONLY);
		if (fd != -1) {
			rump___sysimpl_dup2(fd, 2);
			rump___sysimpl_close(fd);
		}
	}

	for (fd = 3; fd < MAXFD; fd++) {
		if (__franken_fd[fd].valid == 0)
			break;
		switch (__franken_fd[fd].st.st_mode & S_IFMT) {
		case S_IFREG:
			rump_pub_etfs_register(__franken_fd[fd].key, __franken_fd[fd].num, RUMP_ETFS_REG);
			flags = __franken_fd[fd].flags & O_ACCMODE;
			rump___sysimpl_open(__franken_fd[fd].key, flags);
			break;
		case S_IFBLK:
			rump_pub_etfs_register(__franken_fd[fd].key, __franken_fd[fd].num, RUMP_ETFS_BLK);
			if (root == 0) {
				struct ufs_args ufs;

				ufs.fspec = __franken_fd[fd].key;
				flags = __franken_fd[fd].flags & O_ACCMODE;
				if (flags == O_RDWR)
					flags = 0;
				else
					flags = MNT_RDONLY;
				ret = rump___sysimpl_mount50("ffs", "/", flags, &ufs, sizeof(struct ufs_args));
				if (ret == 0) {
					root = 1;
				} else {
					ret = rump___sysimpl_mount50("ext2fs", "/", 0, &ufs, sizeof(struct ufs_args));
					if (ret == 0) {
						root = 1;
					}
				}
			}
			break;
		case S_IFSOCK:
			ret = rump_pub_netconfig_ifcreate(__franken_fd[fd].key);
			if (ret == 0) {
				rump_pub_netconfig_dhcp_ipv4_oneshot(__franken_fd[fd].key);
			}
			break;
		}
	}
}

void
__franken_autoconf()
{
	const int sc[4] = {CTL_NET, CTL_NET_INET6, 41, IPV6CTL_ACCEPT_RTADV};
	int set = 1;
	size_t setlen = sizeof(int);

	/* enable ipv6 autoconf */
	rump___sysimpl___sysctl(sc, 4, NULL, NULL, &set, setlen);
}
