#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void *
calloc(size_t nmemb, size_t size)
{
	size_t n = nmemb * size; /* XXX check for overflow */
	void *m = aligned_alloc(n, 0);

	if (!m)
		return NULL;

	memset(m, 0, n);
	return m;
}
