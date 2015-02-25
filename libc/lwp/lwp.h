#ifndef _LWP_H_
#define _LWP_H_

#include <sys/types.h>

lwpid_t _lwp_self(void);
int _lwp_kill(lwpid_t, int);
void  _lwp_exit(void);

#endif
