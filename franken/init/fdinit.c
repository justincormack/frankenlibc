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
int rump_pub_netconfig_ifup(const char *) __attribute__ ((weak));
int rump_pub_netconfig_ipv4_ifaddr(const char *, const char *, const char *) __attribute__ ((weak));
int rump_pub_netconfig_ipv4_ifaddr_cidr(const char *, const char *, int) __attribute__ ((weak));
int rump_pub_netconfig_ipv4_gw(const char *) __attribute__ ((weak));

int rump_pub_netconfig_ifcreate(const char *interface) {return 0;}
int rump_pub_netconfig_dhcp_ipv4_oneshot(const char *interface) {return 0;}
int rump_pub_netconfig_auto_ipv6(const char *interface) {return 0;}
int rump_pub_netconfig_ifup(const char *interface) {return 0;}
int rump_pub_netconfig_ipv4_ifaddr(const char *interface, const char *addr, const char *mask) {return 0;}
int rump_pub_netconfig_ipv4_ifaddr_cidr(const char *interface, const char *addr, int mask) {return 0;};
int rump_pub_netconfig_ipv4_gw(const char *interface) {return 0;}

struct __fdtable __franken_fd[MAXFD];

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

struct tmpfs_args {
	int ta_version;
	ino_t ta_nodes_max;
	off_t ta_size_max;
	uid_t ta_root_uid;
	gid_t ta_root_gid;
	mode_t ta_root_mode;
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
int rump___sysimpl_mkdir(const char *, mode_t);

#define AF_INET 2
#define AF_INET6 24
#define SOCK_STREAM 1

static void
mount_tmpfs(void)
{
	struct tmpfs_args ta = {
		.ta_version = 1,
		.ta_nodes_max = 0,
		.ta_size_max = 0,
		.ta_root_uid = 0,
		.ta_root_gid = 0,
		.ta_root_mode = 0777,
	};

	/* try to mount tmpfs if possible, useful for ro root fs */
	rump___sysimpl_mkdir("/tmp", 0777);
	/* might fail if no /tmp directory, or tmpfs not included in system */
	rump___sysimpl_mount50("tmpfs", "/tmp", 0, &ta, sizeof(struct tmpfs_args));
}

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

static void
register_net(int fd)
{
	char key[16], num[16];
	int ret;
	char *addr, *mask, *gw;

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
			/* XXX move to autodetect later, but gateway complex */
			addr = getenv("FIXED_ADDRESS");
			mask = getenv("FIXED_MASK");
			gw = getenv("FIXED_GATEWAY");
			if (addr == NULL || mask == NULL || gw == NULL) {
				rump_pub_netconfig_dhcp_ipv4_oneshot(key);
				rump___sysimpl_close(ret);
			} else {
				rump_pub_netconfig_ifup(key);
				rump_pub_netconfig_ipv4_ifaddr_cidr(key, addr, atoi(mask));
				rump_pub_netconfig_ipv4_gw(gw);
			}
		}
	}
}

static int
register_block(int dev, int fd, int flags, off_t size, int root)
{
	char key[16], rkey[16], num[16];
	struct ufs_args ufs;
	int ret;

	mkkey(key, num, "/dev/block", dev, fd);
	mkkey(rkey, num, "/dev/rblock", dev, fd);
	rump_pub_etfs_register_withsize(key, num, RUMP_ETFS_BLK, 0, size);
	rump_pub_etfs_register_withsize(rkey, num, RUMP_ETFS_CHR, 0, size);
	if (root == 0)
		return 0;
	ufs.fspec = key;
	if (flags == O_RDWR)
		flags = MNT_LOG;
	else
		flags = MNT_RDONLY;
	ret = rump___sysimpl_mount50("ffs", "/", flags, &ufs, sizeof(struct ufs_args));
	if (ret == -1) {
		if (flags == MNT_LOG)
			flags = 0;
		ret = rump___sysimpl_mount50("ext2fs", "/", flags, &ufs, sizeof(struct ufs_args));
	}
	if (ret == 0)
		atexit(unmount_atexit);
	return ret;
}

void
__franken_fdinit_create()
{
	int fd;
	int n_reg = 0, n_block = 0;

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

	/* XXX would be nicer to be able to detect a file system,
	   but this also allows us not to mount a block device.
	   Pros and cons, may change if this is not convenient */

	/* only fd 3 will be mounted as root file system */
	if (__franken_fd[3].valid) {
		switch (__franken_fd[fd].st.st_mode & S_IFMT) {
		case S_IFREG:
		case S_IFBLK:
			if (register_block(n_block++, fd,
			    __franken_fd[fd].flags & O_ACCMODE,
			    __franken_fd[fd].st.st_size, 1) == 0) {
				__franken_fd[fd].mounted = 1;
			}
			break;
		case S_IFSOCK:
			register_net(fd);
			break;
		}
	}

	for (fd = 4; fd < MAXFD; fd++) {
		if (__franken_fd[fd].valid == 0)
			break;
		switch (__franken_fd[fd].st.st_mode & S_IFMT) {
		case S_IFREG:
			fd = register_reg(n_reg++, fd, __franken_fd[fd].flags & O_ACCMODE);
			break;
		case S_IFBLK:
			register_block(n_block++, fd, __franken_fd[fd].flags & O_ACCMODE, __franken_fd[fd].st.st_size, 0);
			break;
		case S_IFSOCK:
			register_net(fd);
			break;
		}
	}

	/* now some generic stuff */
	mount_tmpfs();
}
