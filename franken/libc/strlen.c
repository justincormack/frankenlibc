#include <string.h>

size_t strlen(char const *s) __attribute__ ((weak));

size_t
strlen(char const *s)
{
	size_t len = 0;

	while (*s++)
		len++;

	return len;
}
