#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void __assert13(const char *, int, const char *, const char *) __attribute__ ((weak));

void
__assert13(const char *file, int line, const char *function, const char *failedexpr)
{

	abort();
}
