#ifndef _SIGNAL_H_
#define _SIGNAL_H_

#include <sys/types.h>

#include <rename.h>

int kill(pid_t, int);
int raise(int);

#define SIGABRT		6

#endif
