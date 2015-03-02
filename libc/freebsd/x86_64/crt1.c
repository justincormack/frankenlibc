__asm__ (".text\n\t"
	 ".global _start\n\t"
	 "_start:\n\t"
	 "andq	$-16,%rsp\n\t"		/* align stack pointer */
        /* rdi is &argc, argv is (&argc + 8) */
	 "mov	%rdi, %rsi\n\t"		/* argv = &argc + 1 */
	 "mov	(%rdi), %rdi\n\t"	/* argc */
	 "add	$0x08, %rsi\n\t"
	 "mov	%rdi, %rdx\n\t"		/* envp = (argc << 3) + argv */
	 "shl	$3, %rdx\n\t"
	 "add	%rsi, %rdx\n\t"
	 "	call	__platform_init\n\t"
	 "1:	jmp 1b\n\t");
