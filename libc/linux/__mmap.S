#include "syscall.h"

#ifdef SYS_mmap2
SYSCALL(mmap2, __mmap);
#else
SYSCALL(mmap, __mmap);
#endif
