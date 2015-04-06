#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>

#include "fdinit.h"

enum rump_etfs_type {
	RUMP_ETFS_REG,
	RUMP_ETFS_BLK,
	RUMP_ETFS_CHR,
	RUMP_ETFS_DIR,
	RUMP_ETFS_DIR_SUBDIRS
};

int rump_pub_etfs_register(const char *, const char *, enum rump_etfs_type) __attribute__ ((weak));

int
rump_pub_etfs_register(const char *key, const char *hostpath, enum rump_etfs_type ftype)
{

	return 0;
}

struct __fdtable __franken_fd[MAXFD];

/* XXX should have proper functions in libc */
static char *
mkkey(char *key, const char *pre, int fd)
{
	char *k = key;
	int i;

	if (fd > 99) abort();
	for (i = 0; i < strlen(pre); i++)
		*k++ = pre[i];
	if (fd > 9) {
		*k++ = (fd / 10) + '0';
		fd /= 10;
	}
	*k++ = fd + '0';
	*k++ = 0;

	return key;
}

void
__franken_fdinit()
{
	int fd;
	struct stat st;
	char *mem;
	char *key;

	/* iterate over numbered descriptors, stopping when one does not exist */
	for (fd = 0; fd < MAXFD; fd++) {
		memset(&st, 0, sizeof(struct stat));
		if (fstat(fd, &st) == -1) {
			__franken_fd[fd].valid = 0;
			break;
		}
		__franken_fd[fd].valid = 1;
		memcpy(&__franken_fd[fd].st, &st, sizeof(struct stat));
		switch (st.st_mode & S_IFMT) {
		case S_IFREG:
			mem = mmap(0, st.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
			if (mem != MAP_FAILED)
				__franken_fd[fd].flags = PROT_READ | PROT_WRITE;
			if (mem == MAP_FAILED) {
				mem = mmap(0, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
				if (mem != MAP_FAILED)
					__franken_fd[fd].flags = PROT_READ;
			}
			if (mem == MAP_FAILED) {
				__franken_fd[fd].valid = 0;
				break;
			}
			__franken_fd[fd].mem = mem;
			key = mkkey(__franken_fd[fd].key, "/dev/fd", fd);
			rump_pub_etfs_register(key, &key[7], RUMP_ETFS_REG);
			break;
		case S_IFBLK:
			key = mkkey(__franken_fd[fd].key, "/dev/fd", fd);
			rump_pub_etfs_register(key, &key[7], RUMP_ETFS_BLK);
			break;
		case S_IFSOCK:
			/* XXX probably a tap device for network */
			break;
		default:
			break;
		}
	}
}
