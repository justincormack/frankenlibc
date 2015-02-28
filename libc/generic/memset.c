#include <stdlib.h>

/* somewhere else may provide a better memset, so only provide a weak one */

void *memset(void *, int, size_t) __attribute__((weak));

void *memset(void *dest, int c, size_t n)
{
	unsigned char *d = dest;

	while (n--)
		*d++ = c;

	return dest;
}
