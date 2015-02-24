__asm__ (".text\n\t"
	 ".global _start\n\t"
	 "_start:\n\t"
	 "	pop	%rsi\n\t"		/* argc */
	 "	mov	%rsp, %rdx\n\t"		/* argv */
	 "	push	%rsi\n\t"
	 "	mov	%rdi, %rcx\n\t"		/* envp */
	 "	shl	$3, %rcx\n\t"
	 "	add	$8, %rcx\n\t"
	 "	add	%rdx, %rcx\n\t"
	 "	mov	$main,%rdi\n\t"		/* 1st arg: application entry ip */
	 "	call	__libc_start_main\n\t"
	 "1:	jmp 1b\n\t");
