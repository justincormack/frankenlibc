#ifndef _STDLIB_H_
#define _STDLIB_H_

#include <stddef.h>
#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>

void abort(void) __attribute__ ((noreturn));
int atoi(const char *);
int atexit(void (*)(void));
void *calloc(size_t, size_t);
void exit(int) __attribute__ ((noreturn));
void _Exit(int) __attribute__ ((noreturn));
void free(void *);
char *getenv(const char *);
void *malloc(size_t);
int posix_memalign(void **, size_t, size_t);
void *realloc(void *, size_t);

#endif
