/* Written 2011 Nicholas J. Kain, released as Public Domain */
__asm__ (".weak _init\n\t"
	 ".weak _fini\n\t"
	 ".text\n\t"
	 ".global _start\n\t"
	 "_start:\n\t"
	 "	xor %rbp,%rbp\n\t"	/* rbp:undefined -> mark as zero 0 (ABI) */
	 "	mov %rdx,%r9\n\t"	/* 6th arg: ptr to register with atexit() */
	 "	pop %rsi\n\t"		/* 2nd arg: argc */
	 "	mov %rsp,%rdx\n\t"	/* 3rd arg: argv */
	 "	andq $-16,%rsp\n\t"	/* align stack pointer */
	 "	mov $_fini,%r8\n\t"	/* 5th arg: fini/dtors function */
	 "	mov $_init,%rcx\n\t"	/* 4th arg: init/ctors function */
	 "	mov $main,%rdi\n\t"	/* 1st arg: application entry ip */
	 "	call __platform_init\n\t"
	 "1:	jmp 1b\n\t");
