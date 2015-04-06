#ifndef _SIGNAL_H_
#define _SIGNAL_H_

#include <sys/types.h>

#define kill(p, s) __platform_kill(p, s)

int kill(pid_t, int);

#define SIGABRT 6

#endif
