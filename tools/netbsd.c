#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "rumprun.h"

int
filter_init(char *program)
{

	return 0;
}

int
filter_fd(int fd, int flags, mode_t mode)
{

	return 0;
}

int
filter_load_exec(char *program, char **argv, char **envp)
{
	int ret;

	if (execve(program, argv, envp) == -1) {
		perror("execve");
		exit(1);
	}

	return 0;
}

int
tapopen(char *name)
{

	return open(name, O_RDWR);
}
