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
#if defined(__linux__)
#define MAP_ANON    	0x20
#define MAP_STACK	0x20000
#else /* NetBSD */
#define MAP_ANON	0x1000
#define MAP_STACK	0x2000
#endif

/* Linux does not support alignment options for mmap so for now we use and
   emulate the NetBSD values; they do not conflict with any options we use */

#define MAP_ALIGNED(n)		((n) << MAP_ALIGNMENT_SHIFT)
#define MAP_ALIGNMENT_SHIFT	24
#define MAP_ALIGNMENT_MASK	MAP_ALIGNED(0xff)
#define MAP_ALIGNMENT_64KB	MAP_ALIGNED(16) /* 2^16 */
#define MAP_ALIGNMENT_16MB	MAP_ALIGNED(24) /* 2^24 */
#define MAP_ALIGNMENT_4GB	MAP_ALIGNED(32) /* 2^32 */
#define MAP_ALIGNMENT_1TB	MAP_ALIGNED(40) /* 2^40 */
#define MAP_ALIGNMENT_256TB	MAP_ALIGNED(48) /* 2^48 */
#define MAP_ALIGNMENT_64PB	MAP_ALIGNED(56) /* 2^56 */

#define MAP_FAILED ((void *) -1)

void *mmap(void *, size_t, int, int, int, off_t);
int munmap(void *, size_t);

#endif
