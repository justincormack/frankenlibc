#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAXFD 64

struct __fdtable {
	int valid;
	char *mem;
	int flags;
	struct stat st;
};

extern struct __fdtable __franken_fd[MAXFD];
