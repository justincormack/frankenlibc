#include <stdlib.h>
#include <unistd.h>

extern size_t __platform_pagesize;

int
getpagesize(void)
{

	return (int)__platform_pagesize;
}
