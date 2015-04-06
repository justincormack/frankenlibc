#ifndef _LINUX_GETRANDOM_H_
#define _LINUX_GETRANDOM_H_

#include <stddef.h>
#include <stdlib.h>

#define getrandom(b, s, f) __platform_getrandom(b, s, f)

int getrandom(void *, size_t, unsigned int);

#endif
