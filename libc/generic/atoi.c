#include <ctype.h>
#include <stdlib.h>

int
atoi(const char *str)
{
	int ret = 0;
	int pos = 1;

	for (; isspace((int)(unsigned char)*str); str++);

	if (*str == '-') {
		pos = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9') {
		ret *= 10;
		ret += pos * (*str++ - '0');
	}

	return ret;
}
