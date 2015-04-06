#include <stdlib.h>
#include <unistd.h>

#include "linux.h"

extern size_t __pagesize;

int
getpagesize(void)
{

#ifdef HUGEPAGESIZE
	return HUGEPAGESIZE;
#else
	return (int)__pagesize;
#endif
}
