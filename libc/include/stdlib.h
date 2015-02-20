#ifndef _STDLIB_H_
#define _STDLIB_H_

#include <stddef.h>
#include <sys/cdefs.h>

typedef unsigned long size_t;
typedef long ssize_t;

void abort(void);
void *aligned_alloc(size_t, size_t);
void *calloc(size_t, size_t);
void exit(int);
void free(void *);
char *getenv(const char *);
void *malloc(size_t);

#endif
