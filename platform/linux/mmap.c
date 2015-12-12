#include <errno.h>
#include <stdint.h>
#include <sys/mman.h>

#include "syscall.h"

#include "linux.h"

#define UNIT SYSCALL_MMAP2_UNIT

extern size_t __pagesize;

#ifdef HUGEPAGESIZE
static int usehuge = 1;
#endif

static void *
__mmap(void *addr, size_t length, int prot, int nflags, int fd, off_t offset)
{

#ifdef SYS_mmap2
	return (void *)syscall(SYS_mmap2, addr, length, prot, nflags, fd, offset / UNIT);
#else
	return (void *)syscall(SYS_mmap, addr, length, prot, nflags, fd, offset);
#endif
}

void *
mmap(void *addr, size_t length, int prot, int nflags, int fd, off_t offset)
{
	int flags = (nflags & MAP_SHARED ? LINUX_MAP_SHARED : 0) | 
		    (nflags & MAP_PRIVATE ? LINUX_MAP_PRIVATE : 0) |
		    (nflags & MAP_FIXED ? LINUX_MAP_FIXED : 0) |
		    (nflags & MAP_ANON ? LINUX_MAP_ANON : 0) |
		    (nflags & MAP_STACK ? LINUX_MAP_STACK : 0);

#ifdef HUGEPAGESIZE
	if (usehuge && length >= HUGEPAGESIZE && (align == 0 || (1L << align) <= HUGEPAGESIZE)) {
		mem = __mmap(addr, length, prot, flags | LINUX_MAP_HUGE(HUGEPAGESIZE), fd, offset);
		if (mem != MAP_FAILED)
			return mem;
		usehuge = 0;
	}
#endif

	return __mmap(addr, length, prot, flags, fd, offset);
}
