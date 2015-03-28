#include <sys/mman.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <unistd.h>

int
main()
{
	void *mem;
	int ret;
	int i;
	int pgsize = getpagesize();

	assert(pgsize >= 4096);

	/* standard mmap and munmap */
	mem = mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	assert(mem != MAP_FAILED);
	ret = munmap(mem, 4096);
	assert(ret == 0);

	/* test aligned allocations */
	for (i = 12; i < 24; i++) {
		long align = 1L << i;
		long mask = align - 1L;
		long testalign;

		if (align < pgsize)
			continue;
		mem = mmap(0, align, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON | MAP_ALIGNED(i), -1, 0);
		if (mem == MAP_FAILED)
			break;
		testalign = (long)mem & mask;
		assert(testalign == 0);
		ret = munmap(mem, align);
		assert(ret == 0);
	}

	/* test failure cases */
	mem = mmap(0, (size_t)__LONG_MAX__, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, 9999, 0);
	assert(mem == MAP_FAILED);
	assert(errno > 0);

	return 0;
}
