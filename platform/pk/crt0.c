/*
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
*/

__asm__("\
.text \n\
.global _start \n\
_start: \n\
	la gp, _gp \n\
	la t0, _fbss \n\
	la t1, _end \n\
1: \n\
	sd x0, 0(t0) \n\
	addi t0, t0, 8 \n\
	bltu t0, t1, 1b \n\
	# argc, argv, envp \n\
	lw a0, 0(sp) \n\
	addi a1, sp, 8 \n\
	li a2, 0 \n\
	call __cstart \n\
	ret \n\
");

int main();
void _init() __attribute__((weak));
void _fini() __attribute__((weak));
_Noreturn int __libc_start_main(int (*)(), int, char **,
	void (*)(), void(*)(), void(*)());

void __cstart(int argc, char **argv, char **envp)
{

	__libc_start_main(main, argc, argv, _init, _fini, 0);
}
