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
int rump_pub_etfs_register_withsize(const char *, const char *, enum rump_etfs_type, uint64_t, uint64_t);
int rump_pub_etfs_remove(const char *);

int rump_pub_netconfig_ifcreate(const char *) __attribute__ ((weak));
int rump_pub_netconfig_dhcp_ipv4_oneshot(const char *) __attribute__ ((weak));
int rump_pub_netconfig_auto_ipv6(const char *) __attribute__ ((weak));

int rump_pub_netconfig_ifcreate(const char *interface) {return 0;}
int rump_pub_netconfig_dhcp_ipv4_oneshot(const char *interface) {return 0;}
int rump_pub_netconfig_auto_ipv6(const char *interface) {return 0;}

struct __fdtable __franken_fd[MAXFD];

/* XXX should have proper functions in libc */
void
mkkey(char *k, char *n, const char *pre, int dev, int fd)
{
	int i, d;

	if (fd > 99 || dev > 99) abort();
	for (i = 0; i < strlen(pre); i++)
		*k++ = pre[i];
	if (dev > 9) {
		d = (dev / 10) + '0';
		*k++ = d;
		dev /= 10;
	}
	d = dev + '0';
	*k++ = d;
	*k++ = 0;

	if (fd > 9) {
		d = (fd / 10) + '0';
		*n++ = d;
		fd /= 10;
	}
	d = fd + '0';
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
		/* XXX move this to platform code */
		switch (st.st_mode & S_IFMT) {
		case S_IFREG:
			__franken_fd[fd].seek = 1;
			break;
		case S_IFBLK:
			__franken_fd[fd].seek = 1;
			break;
		case S_IFCHR:
			/* XXX Linux presents stdin as char device see notes to clean up */
			__franken_fd[fd].seek = 0;
			break;
		case S_IFIFO:
			__franken_fd[fd].seek = 0;
			break;
		case S_IFSOCK:
			__franken_fd[fd].seek = 0;
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
#define MNT_LOG		0x02000000
#define MNT_FORCE	0x00080000

int rump___sysimpl_open(const char *, int, ...);
int rump___sysimpl_close(int);
int rump___sysimpl_dup2(int, int);
int rump___sysimpl_mount50(const char *, const char *, int, void *, size_t);
int rump___sysimpl_unmount(const char *, int);
int rump___sysimpl_socket30(int, int, int);

#define AF_INET 2
#define AF_INET6 24
#define SOCK_STREAM 1

static void
unmount_atexit(void)
{
	int ret __attribute__((__unused__));

	ret = rump___sysimpl_unmount("/", MNT_FORCE);
}

static int
register_reg(int dev, int fd, int flags)
{
	char key[16], num[16];

	mkkey(key, num, "/dev/vfile", dev, fd);
	rump_pub_etfs_register(key, num, RUMP_ETFS_REG);
	return rump___sysimpl_open(key, flags);
}

void
__franken_fdinit_create()
{
	int fd, ret, flags;
	int root = 0;
	char key[16], rkey[16], num[16];
	int n_reg = 0, n_block = 0;
	struct ufs_args ufs;

	if (__franken_fd[0].valid) {
		fd = register_reg(n_reg++, 0, O_RDONLY);
		if (fd != -1) {
			rump___sysimpl_dup2(fd, 0);
			rump___sysimpl_close(fd);
		}
	}
	if (__franken_fd[1].valid) {
		fd = register_reg(n_reg++, 1, O_WRONLY);
		if (fd != -1) {
			rump___sysimpl_dup2(fd, 1);
			rump___sysimpl_close(fd);
		}
	}

	if (__franken_fd[2].valid) {
		fd = register_reg(n_reg++, 2, O_WRONLY);
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
			fd = register_reg(n_reg++, fd, __franken_fd[fd].flags & O_ACCMODE);
			break;
		case S_IFBLK:
			mkkey(key, num, "/dev/block", n_block, fd);
			mkkey(rkey, num, "/dev/rblock", n_block, fd);
			n_block++;
			rump_pub_etfs_register_withsize(key, num,
				RUMP_ETFS_BLK, 0, __franken_fd[fd].st.st_size);
			rump_pub_etfs_register_withsize(rkey, num,
				RUMP_ETFS_CHR, 0, __franken_fd[fd].st.st_size);
			if (root == 0) {
				ufs.fspec = key;
				flags = __franken_fd[fd].flags & O_ACCMODE;
				if (flags == O_RDWR)
					flags = MNT_LOG;
				else
					flags = MNT_RDONLY;
				ret = rump___sysimpl_mount50("ffs", "/", flags, &ufs, sizeof(struct ufs_args));
				if (ret == 0) {
					root = 1;
				} else {
					if (flags == MNT_LOG)
						flags = 0;
					ret = rump___sysimpl_mount50("ext2fs", "/", flags, &ufs, sizeof(struct ufs_args));
					if (ret == 0) {
						root = 1;
					}
				}
				if (root == 1)
					atexit(unmount_atexit);
			}
			break;
		case S_IFSOCK:
			mkkey(key, num, "virt", fd, fd);
			ret = rump_pub_netconfig_ifcreate(key);
			if (ret == 0) {
				ret = rump___sysimpl_socket30(AF_INET6, SOCK_STREAM, 0);
				if (ret != -1) {
					rump_pub_netconfig_auto_ipv6(key);
					rump___sysimpl_close(ret);
				}
				ret = rump___sysimpl_socket30(AF_INET, SOCK_STREAM, 0);
				if (ret != -1) {
					rump_pub_netconfig_dhcp_ipv4_oneshot(key);
					rump___sysimpl_close(ret);
				}
			}
			break;
		}
	}
}
