#include <stdlib.h>

static int
isspace(int c)
{
	return c == ' ' || (c >= '\t' && c <= '\r');
}

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
