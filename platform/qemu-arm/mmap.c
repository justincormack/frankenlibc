#include <errno.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>

#define CORESIZE 16777216

static char __core[CORESIZE];

static uintptr_t core_base = (uintptr_t) &__core;
static uintptr_t core_top = (uintptr_t) &__core[CORESIZE];

void *
mmap(void *addr, size_t length, int prot, int nflags, int fd, off_t offset)
{
        unsigned int shift;
	uintptr_t align;
        uintptr_t amask;
	int pagesize = getpagesize();
	void *mem;

	if (fd != -1 || offset != 0 || addr) {
		errno = EINVAL;
		return MAP_FAILED;
	}

	shift = (nflags & MAP_ALIGNMENT_MASK) >> MAP_ALIGNMENT_SHIFT;
	if (shift == 0) {
		align = pagesize;
	} else {
		align = 1UL << shift;
	}
	amask = align - 1UL;

	if ((core_base & amask) != 0)
		core_base = (core_base & ~amask) + align;

	if (core_base + length > core_top) {
		errno = ENOMEM;
		return MAP_FAILED;
	}

	mem = (void *)core_base;

	core_base += length;

	return mem;
}

int
munmap(void *addr, size_t length)
{

	/* XXX at least at end of mapping could reclaim */
	return 0;
}
