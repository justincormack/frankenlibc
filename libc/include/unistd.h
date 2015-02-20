#ifndef _UNISTD_H_
#define _UNISTD_H_

#include <stdlib.h>
#include <sys/types.h>

#define MAXHOSTNAMELEN 64

void _exit(int);
int fsync(int);
int gethostname(char *, size_t);
int getpagesize(void);
pid_t getpid(void);
ssize_t pread(int, void *, size_t, off_t);
ssize_t pwrite(int, const void *, size_t, off_t);
ssize_t write(int, const void *, size_t);

#endif
