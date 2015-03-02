#include "syscall.h"

#ifdef SYSCALL_MMAP
SYSCALL_MMAP(mmap, mmap);
#else
SYSCALL(mmap, mmap);
#endif
