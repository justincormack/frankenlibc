#include "syscall.h"

#ifdef SYS_pread64
SYSCALL(pread64, __pread);
#else
SYSCALL(pread, __pread);
#endif
