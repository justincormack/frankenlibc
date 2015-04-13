#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "rumprun.h"

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
	int fd;
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

	/* accept more existing fds */

	for (i = 1; i < argc; i++) {
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
		if (strchr(arg, ':')) {
			char *colon = strchr(arg, ':');
			char *pre;

			pre = strndup(arg, colon - arg);
			fd = colon_open(pre, &colon[1]);
			free(pre);
			if (fd == -1)
				continue;
		} else {
			fd = open(arg, access);
			if (fd == -1) {
				perror("open");
				exit(1);
			}
		}
		fds[nfds].fd = fd;
		fds[nfds].flags = access;
		fds[nfds].mode = 0;
		nfds++;
	}

	for (; i < argc; i++)
		pargs[p++] = argv[i];

	pargs[p] = "\0";

	for (; p < argc; p++)
		pargs[p] = 0;

	ret = filter_init(program);
	if (ret < 0) {
		fprintf(stderr, "filter_init failed\n");
		abort();
	}

	for (i = 0; i < nfds; i++) {
		int fl;

		fl = fcntl(fd, F_GETFL);
		if (fl == -1) {
			perror("fcntl");
			abort();
		}
		ret = fcntl(fd, F_SETFL, fl | O_NONBLOCK);

		ret = filter_fd(fds[i].fd, fds[i].flags, fds[i].mode);
		if (ret < 0) {
			fprintf(stderr, "filter_fd failed\n");
			abort();
		}
	}

	ret = chdir("/");

	ret = filter_load_exec(program, pargs, environ);
	if (ret < 0) {
		fprintf(stderr, "filter_load_exec failed\n");
		abort();
	}

	return 0;	
}

int
colon_open(char *pre, char *post)
{
	int fd, ret;

	/* open file as console for writing, use /dev/null as input */
	if (strcmp(pre, "console") == 0) {
		fd = open(post, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
		if (fd == -1) {
			perror("console open");
			exit(1);
		}
		ret = dup2(fd, 1);
		if (ret == -1) {
			perror("dup2");
			exit(1);
		}
		ret = dup2(fd, 2);
		if (ret == -1) {
			perror("dup2");
			exit(1);
		}
		close(fd);
		fd = open("/dev/null", O_RDONLY);
		if (ret == -1) {
			perror("open /dev/null");
			exit(1);
		}
		ret = dup2(fd, 0);
		if (ret == -1) {
			perror("dup2");
			exit(1);
		}
		close(fd);
		return -1;
	}

	/* call OS specific handler */

	return -1;
}
