#ifndef _LWP_H_
#define _LWP_H_

#include <time.h>
#include <sys/types.h>

void  _lwp_exit(void);
int _lwp_kill(lwpid_t, int);
int ___lwp_park60(clockid_t, int, const struct timespec *, lwpid_t, const void *, const void *);
lwpid_t _lwp_self(void);

#endif
