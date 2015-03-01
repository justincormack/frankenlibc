__asm__ (".txt\n\t"
	 ".global _start \n\t"
	 "_start:\n\t"
	 "	pushl	%ebx\n\t"
	 "	pushl	%ecx\n\t"
	 "	pushl	%edx\n\t"
	 "	call	__platform_init\n\t"
	 "1:	jmp	1b\n\t");
