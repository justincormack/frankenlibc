#include "syscall.h"

#ifdef SYSCALL6
SYSCALL6(mmap, __platform_mmap);
#else
SYSCALL(mmap, __platform_mmap);
#endif
