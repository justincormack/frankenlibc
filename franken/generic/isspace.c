#include <ctype.h>

int isspace(int) __attribute ((weak));

int
isspace(int c)
{
	return c == ' ' || (c >= '\t' && c <= '\r');
}
