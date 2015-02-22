#include <sys/mman.h>

int madvise(void *, size_t, int);

int
madvise(void *addr, size_t length, int advice)
{

	/* thanks for the advice */
	return 0;
}
