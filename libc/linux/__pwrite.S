#include "syscall.h"

#ifdef SYS_pwrite64
SYSCALL(pwrite64, __pwrite);
#else
SYSCALL(pwrite, __pwrite);
#endif
