#include <stdlib.h>
#include <errno.h>

int
posix_memalign(void **ptr, size_t align, size_t size)
{

	*ptr = aligned_alloc(align, size);
	if (*ptr == NULL)
		return ENOMEM;
	return 0;
}
