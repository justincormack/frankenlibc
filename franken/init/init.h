#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netinet/in.h>

#define MAXFD 64

struct __fdtable {
	int valid;
	char *mem;
	int flags;
	int seek;
	struct stat st;
	struct thread *wake;
	int mounted;
	int hasaddr;
	struct in_addr addr;
	struct in_addr netmask;
	struct in_addr broadcast;
	struct in_addr gateway;
};

extern struct __fdtable __franken_fd[MAXFD];

void __franken_fdinit(void);
void __franken_fdinit_create(void);
