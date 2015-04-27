#include "syscall.h"

#include "linux.h"

int __platform_set_thread_area(void *);

#ifdef SYS_arch_prctl
int __arch_prctl(int, void *);

int
__platform_set_thread_area(void *p)
{

	return syscall(SYS_arch_prctl, ARCH_SET_FS, TP_ADJ(p));
}
#else
int
__platform_set_thread_area(void *p)
{

	return 0;
}
#endif
