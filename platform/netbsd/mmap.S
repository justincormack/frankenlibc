#include "syscall.h"

#ifdef SYSCALL_MMAP
SYSCALL_MMAP(mmap, __platform_mmap);
#else
SYSCALL(mmap, __platform_mmap);
#endif
