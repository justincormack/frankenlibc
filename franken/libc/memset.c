#include <stdlib.h>

void *memset(void *dest, int c, size_t n)
{
	unsigned char *d = dest;

	while (n--)
		*d++ = c;

	return dest;
}
