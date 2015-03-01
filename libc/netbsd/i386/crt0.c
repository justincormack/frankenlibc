__asm__ (".text\n\t"
	 ".global __start \n\t"
	 "__start:\n\t"
	 "	pushl	%ebx\n\t"
	 "	pushl	%ecx\n\t"
	 "	pushl	%edx\n\t"
	 "	call	__platform_init\n\t"
	 "1:	jmp	1b\n\t");
