#ifndef _UNISTD_H_
#define _UNISTD_H_

#include <stdlib.h>
#include <sys/types.h>

#include <rename.h>

void _exit(int) __attribute__ ((noreturn));
int getpagesize(void);
int isatty(int);
ssize_t write(int, const void *, size_t);

#endif
