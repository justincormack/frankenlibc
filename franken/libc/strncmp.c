#include <string.h>

int
strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned const char *u1 = (unsigned char const *)s1;
	unsigned const char *u2 = (unsigned char const *)s2;

	while (--n && *u1 && *u2 && *u1 == *u2) {
		u1++;
		u2++;
	}

	return *u1 - *u2;
}
