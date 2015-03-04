#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAXFD 64

struct __fdtable {
	int valid;
	off_t size;
	mode_t mode;
	char *mem;
	int flags;
};

extern struct __fdtable __franken_fd[MAXFD];
