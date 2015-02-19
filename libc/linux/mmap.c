#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

void *__mmap(void *, size_t, int, int, int, off_t);

void *
mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
	long align = (flags & MAP_ALIGNMENT_MASK) >> MAP_ALIGNMENT_SHIFT;
	long amask = (1L << align) - 1L;
	long off;

	flags &= ~MAP_ALIGNMENT_MASK;
	if (align == 0 || (1L << align) <= getpagesize()) {
		return __mmap(addr, length, prot, flags, fd, offset);
	}

	addr = __mmap(NULL, length * 2, prot, flags, -1, 0);
	if (addr == MAP_FAILED)
		return MAP_FAILED;

	off = (long) addr & amask;

	if (off == 0) { /* we were lucky, just unmap the excess */
		if (munmap(addr + length, length) == -1)
			abort();
		return addr;
	}

	if (munmap(addr, length * 2) == -1)
		abort();

	return __mmap((char *)addr + length - off, length, prot, flags | MAP_FIXED, -1, 0);
}
