#include <sys/mman.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

int
main()
{
	void *mem;
	int ret;

	mem = mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	assert(mem != MAP_FAILED);
	ret = munmap(mem, 4096);
	assert(ret == 0);

	return 0;
}
