#include <sys/capability.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "filter.h"

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
filter_fd(int fd, int flags, mode_t mode)
{
	cap_rights_t rights;
	int ret;

	/* XXX do read write correctly */
	/* XXX filter exact ioctl */
	cap_rights_init(&rights, CAP_READ, CAP_WRITE, CAP_FSTAT, CAP_IOCTL, CAP_MMAP_RW);
	ret = cap_rights_limit(fd, &rights);
	if (ret == -1) return ret;

	return 0;
}

int
filter_load_exec(char *program, char **argv, char **envp)
{

	if (fexecve(pfd, argv, envp) == -1) {
		perror("fexecve");
		exit(1);
	}

	return 0;
}
