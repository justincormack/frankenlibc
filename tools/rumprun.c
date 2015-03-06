#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "filter.h"

/* this will develop into full wrapper */

/* currently just open files; will understand some special files too */

extern char **environ;

static void
usage(char *name)
{

	printf("Usage: %s program [-ro|-rw] [files] [-- args]\n", name);
	exit(1);
}

struct fdinfo {
	int fd;
	int flags;
	mode_t mode;
};

int
main(int argc, char **argv)
{
	int i, p = 0;
	char *program = NULL;
	char *pargs[argc];
	int access = O_RDWR;
	int ret;
	struct timespec ts;
	struct fdinfo *fds;
	int nfds = 3;

	if (argc < 2)
		usage(argv[0]);

	fds = (struct fdinfo *) calloc(argc + 3, sizeof(struct fdinfo));
	fds[0].fd = 0;
	fds[0].flags = O_RDONLY;
	fds[0].mode = 0;
	fds[1].fd = 1;
	fds[1].flags = O_WRONLY;
	fds[1].mode = 0;
	fds[2].fd = 2;
	fds[2].flags = O_WRONLY;
	fds[2].mode = 0;

	for (i = 1; i < argc; i++) {
		int fd;
		char *arg = argv[i];

		if (strcmp(arg, "-h") == 0)
			usage(argv[0]);
		if (i == 1) {
			program = arg;
			pargs[p++] = program;
			continue;
		}
		if (strcmp(arg, "-ro") == 0) {
			access = O_RDONLY;
			continue;
		}
		if (strcmp(arg, "-rw") == 0) {
			access = O_RDWR;
			continue;
		}
		if (strcmp(arg, "--") == 0) {
			i++;
			break;			
		}
		fd = open(arg, access);
		if (fd == -1) {
			perror("open");
			exit(1);
		}
		fds[nfds++].fd = fd;
		fds[nfds++].flags = access;
		fds[nfds++].mode = 0;
	}

	for (; i < argc; i++)
		pargs[p++] = argv[i];

	pargs[p] = "\0";

	for (; p < argc; p++)
		pargs[p] = 0;

	ret = filter_init(program);
	if (ret < 0) abort();

	for (i = 0; i < nfds; i++) {
		ret = filter_fd(fds[i].fd, fds[i].flags, fds[i].mode);
		if (ret < 0) abort();
	}

	ret = filter_load_exec(program, pargs, environ);
	if (ret < 0) abort();

	return 0;	
}
