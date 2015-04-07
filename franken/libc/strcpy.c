#include <string.h>

char *
strcpy(char *dest, const char *src)
{
	char *i = dest;

	while ((*i++ = *src++));

	return dest;
}
