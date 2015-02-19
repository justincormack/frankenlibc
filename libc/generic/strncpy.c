#include <string.h>

char *
strncpy(char *dest, const char *src, size_t n)
{
	char *d;

	for (d = dest; n > 0; n--)
		if (*src != '\0')
			*(d++) = *(src++);
		else
			/* pad the remainder of dest */
			*(d++) = '\0';

	return dest;
}
