#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAXFD 64

struct __fdtable {
	int valid;
	char *mem;
	int flags;
	int seek;
	struct stat st;
	struct thread *wake;
	int mounted;
};

extern struct __fdtable __franken_fd[MAXFD];

void __franken_fdinit(void);
void __franken_fdinit_create(void);
