#ifndef _ERRNO_H_
#define _ERRNO_H_

#include <sys/errno.h>

extern int errno;

int *__errno(void);

#endif
