#include <stdlib.h>
#include <unistd.h>

#include "linux.h"

extern size_t __platform_pagesize;

int
getpagesize(void)
{

#ifdef HUGEPAGESIZE
	return HUGEPAGESIZE;
#else
	return (int)__platform_pagesize;
#endif
}
