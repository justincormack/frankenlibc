#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>

#include "fdinit.h"

struct __fdtable __franken_fd[MAXFD];

void
__franken_fdinit()
{
	int fd;
	struct stat st;
	char *mem;

	for (fd = 0; fd < MAXFD; fd++) {
		if (fstat(fd, &st) == -1) {
			__franken_fd[fd].valid = 0;
			continue;
		}
		__franken_fd[fd].valid = 1;
		memcpy(&__franken_fd[fd].st, &st, sizeof(struct stat));
		switch (st.st_mode & S_IFMT) {
		case S_IFREG:
			mem = mmap(0, st.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
			if (mem != MAP_FAILED)
				__franken_fd[fd].flags = PROT_READ | PROT_WRITE;
			if (mem == MAP_FAILED) {
				mem = mmap(0, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
				if (mem != MAP_FAILED)
					__franken_fd[fd].flags = PROT_READ;
			}
			if (mem == MAP_FAILED)
				__franken_fd[fd].valid = 0;
			else
				__franken_fd[fd].mem = mem;
			break;
		case S_IFBLK:
			/* XXX handle block devices but not via mmap */
			break;
		case S_IFSOCK:
			/* XXX probably a tap device for network */
			break;
		default:
			break;
		}
	}
}
