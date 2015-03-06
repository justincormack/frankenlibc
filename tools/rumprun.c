#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

/* this will develop into full wrapper */

/* currently just open files; will understand some special files too */

extern char **environ;

static void
usage(char *name)
{

	printf("Usage: %s program [-ro|-rw] [files] [-- args]\n", name);
	exit(1);
}

int
main(int argc, char **argv)
{
	int i, p = 0;
	char *program = NULL;
	char *pargs[argc];
	int access = O_RDWR;
	int ret;
	struct timespec ts;

	if (argc < 2)
		usage(argv[0]);

	ret = filter_init();
	if (ret < 0) abort();

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
		ret = filter_fd(fd, access, 0); /* XXX add type from fstat */
		if (ret < 0) abort();
	}

	for (; i < argc; i++)
		pargs[p++] = argv[i];

	pargs[p] = "\0";

	for (; p < argc; p++)
		pargs[p] = 0;

	/* only fexecve with a CLOEXEC fd really safe here */
	ret = filter_execve(-1);
	if (ret < 0) abort();

	ret = filter_load();
	if (ret < 0) abort();

	if (execve(program, pargs, environ) == -1) {
		perror("execve");
		exit(1);
	}

	return 0;	
}
