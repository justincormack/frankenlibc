#include <string.h>

char *strchr(const char *, int) __attribute__ ((weak));

char *
strchr(const char *s, int c)
{
	unsigned const char *ls;
	unsigned char lc = c;

	for (ls = (unsigned const char *)s; *ls != '\0'; ls++)
		if (*ls == lc)
			return (char *)ls;
	return (lc == '\0') ? (char *)ls : NULL;
}
