#include "syscall.h"

#ifdef SYS_fstat64
SYSCALL(fstat64, __fstat);
#else
SYSCALL(fstat, __fstat);
#endif
