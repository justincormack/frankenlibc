#include <string.h>

char *strcpy(char *, const char *) __attribute__ ((weak));

char *
strcpy(char *dest, const char *src)
{
	char *i = dest;

	while ((*i++ = *src++));

	return dest;
}
