#ifndef _LINUX_GETRANDOM_H_
#define _LINUX_GETRANDOM_H_

#include <stddef.h>
#include <stdlib.h>

int getrandom(void *, size_t, unsigned int);

#endif
