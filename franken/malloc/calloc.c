#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void *
calloc(size_t nmemb, size_t size)
{
	size_t n = nmemb * size; /* XXX check for overflow */
	void *mem = aligned_alloc(sizeof(void *), n);

	if (! mem)
		return NULL;

	memset(mem, 0, n);

	return mem;
}
