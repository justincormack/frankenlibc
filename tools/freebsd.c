#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/disk.h>
#include <sys/socket.h>
#include <net/if.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "rumprun.h"

#ifdef NOCAPSICUM
int
filter_init(char *program)
{

	return 0;
}

int
filter_fd(int fd, int flags, struct stat *st)
{

	return 0;
}

int
filter_load_exec(char *program, char **argv, char **envp)
{
	int ret, pfd;

	pfd = open(program, O_EXEC | O_CLOEXEC);
	if (pfd == -1) {
		perror("open");
		exit(1);
	}

	emptydir();

	if (fexecve(pfd, argv, envp) == -1) {
		perror("fexecve");
		exit(1);
	}

	return 0;
}
#else

#include <sys/capability.h>

int pfd = -1;

int
filter_init(char *program)
{
	cap_rights_t rights;
	int ret;

	pfd = open(program, O_EXEC | O_CLOEXEC);
	if (pfd == -1) {
		perror("open");
		exit(1);
	}

	if (cap_enter() == -1) {
		perror("cap_enter");
		exit(1);
	}

	return 0;
}

int
filter_fd(int fd, int flags, struct stat *st)
{
	cap_rights_t rights;
	int ret;
	unsigned long ioctlb[1] = {DIOCGMEDIASIZE};
	unsigned long ioctlc[1] = {SIOCGIFADDR};

	/* XXX we could cut capabilities down a little further */

	switch (flags & O_ACCMODE) {
	case O_RDONLY:
		if (S_ISBLK(st->st_mode) || S_ISCHR(st->st_mode)) {
			cap_rights_init(&rights, CAP_READ, \
				CAP_SEEK, CAP_FSYNC, CAP_FSTAT, CAP_IOCTL);
		} else {
			cap_rights_init(&rights, CAP_READ, \
				CAP_SEEK, CAP_FSYNC, CAP_FSTAT);
		}
		break;
	case O_WRONLY:
		if (S_ISBLK(st->st_mode) || S_ISCHR(st->st_mode)) {
			cap_rights_init(&rights, CAP_WRITE, \
				CAP_SEEK, CAP_FSYNC, CAP_FSTAT, CAP_IOCTL);
		} else {
			cap_rights_init(&rights, CAP_WRITE, \
				CAP_SEEK, CAP_FSYNC, CAP_FSTAT);
		}
		break;
	case O_RDWR:
		if (S_ISBLK(st->st_mode) || S_ISCHR(st->st_mode)) {
			cap_rights_init(&rights, CAP_READ, CAP_WRITE, \
				CAP_SEEK, CAP_FSYNC, CAP_FSTAT, CAP_IOCTL);
		} else {
			cap_rights_init(&rights, CAP_READ, CAP_WRITE, \
				CAP_SEEK, CAP_FSYNC, CAP_FSTAT);
		}
		break;
	default:
		abort();
	}
	ret = cap_rights_limit(fd, &rights);
	if (ret == -1) return ret;

	if (S_ISBLK(st->st_mode)) {
		ret = cap_ioctls_limit(fd, ioctlb, 1);
		if (ret == -1) return ret;
	} else if (S_ISCHR(st->st_mode)) {
		ret = cap_ioctls_limit(fd, ioctlc, 1);
		if (ret == -1) return ret;
	}

	return 0;
}

int
filter_load_exec(char *program, char **argv, char **envp)
{

	chdir("/");

	if (fexecve(pfd, argv, envp) == -1) {
		perror("fexecve");
		exit(1);
	}

	return 0;
}
#endif /* CAPSICUM */

int
os_pre()
{

	return 0;
}

int
os_open(char *pre, char *post)
{

	fprintf(stderr, "platform does not support %s:%s\n", pre, post);
	exit(1);
}
