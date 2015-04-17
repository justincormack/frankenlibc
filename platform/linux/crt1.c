#include <features.h>

__asm__ ("\
	.section \".note.ABI-tag\", \"a\" \n\
	.p2align 2 \n\
	.long 1f - 0f \n\
	.long 3f - 2f \n\
	.long  1 \n\
0:	.asciz \"GNU\" \n\
1:	.p2align 2 \n\
2:	.long 0 \n\
	.long 3 \n\
	.long 0 \n\
	.long 0 \n\
3:	.p2align 2 \n\
	.text \n\
");

#include "crt_arch.h"

int main();
void _init() __attribute__((weak));
void _fini() __attribute__((weak));
_Noreturn int __libc_start_main(int (*)(), int, char **,
	void (*)(), void(*)(), void(*)());

void __cstart(long *p)
{
	int argc = p[0];
	char **argv = (void *)(p+1);
	__libc_start_main(main, argc, argv, _init, _fini, 0);
}
