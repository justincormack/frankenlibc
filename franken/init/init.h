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
	char key[16];
};

extern struct __fdtable __franken_fd[MAXFD];

void __franken_fdinit(void);
void __franken_autoconf(void);
