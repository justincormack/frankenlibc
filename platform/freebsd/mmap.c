#include <errno.h>
#include <stdint.h>
#include <sys/mman.h>

#include "syscall.h"

/* most FreeBSD flags identical */
#define FREEBSD_MAP_STACK		0x0400
#define FREEBSD_MAP_ALIGNED_SUPER	MAP_ALIGNED(1)

void *__mmap(void *, size_t, int, int, int, off_t);

#ifdef HUGEPAGESIZE
static int usehuge = 1;
#endif

/* XXX check how 32 bit deals with off_t */

void *
mmap(void *addr, size_t length, int prot, int nflags, int fd, off_t offset)
{
	int flags = nflags & (~MAP_STACK);

	if (nflags & MAP_STACK)
		flags |= FREEBSD_MAP_STACK; 

#ifdef HUGEPAGESIZE
	if (usehuge && length >= HUGEPAGESIZE) {
		void *mem = __mmap(addr, length, prot, flags | FREEBSD_MAP_ALIGNED_SUPER, fd, offset);
		if (mem != MAP_FAILED)
			return mem;
		usehuge = 0;
	}
#endif

	return __mmap(addr, length, prot, flags, fd, offset);
}
