#ifndef _SYS_MMAN_H_
#define _SYS_MMAN_H_

#include <stdlib.h>
#include <sys/types.h>

#define PROT_NONE  	0x0
#define PROT_READ  	0x1
#define PROT_WRITE 	0x2
#define PROT_EXEC  	0x4

#define MAP_SHARED  	0x01
#define MAP_PRIVATE 	0x02
#define MAP_FIXED	0x10
#define MAP_ANON	0x1000
#define MAP_STACK	0x2000

#define MAP_FAILED ((void *) -1)

#define mmap(a, b, c, d, e, f) __platform_mmap(a, b, c, d, e, f)

void *mmap(void *, size_t, int, int, int, off_t);
int munmap(void *, size_t);
int mprotect(void *, size_t, int);

#endif
