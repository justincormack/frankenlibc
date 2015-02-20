#ifndef _STRING_H_
#define _STRING_H_

#include <stdlib.h>

void *memcpy(void *, const void *, size_t);
void *memset(void *, int, size_t);
int strcmp(const char *, const char *);
char *strcpy(char *, const char *);
char *strdup(const char *);
size_t strlen(const char *);
char *strncpy(char *, const char *, size_t);

#endif
