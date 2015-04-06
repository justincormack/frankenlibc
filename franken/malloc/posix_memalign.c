#include <stdlib.h>
#include <errno.h>

int
posix_memalign(void **ptr, size_t align, size_t size)
{
	void *mem = aligned_alloc(align, size);

	if (mem == NULL)
		return ENOMEM;

	*ptr = mem;
	return 0;
}
