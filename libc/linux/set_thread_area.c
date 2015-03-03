#include "syscall.h"

int __arch_prctl(int, void *);

int
__platform_set_thread_area(void *p)
{

	return __arch_prctl(ARCH_SET_FS, TP_ADJ(p));
}
