__asm__ (".text\n\t"
	 ".global _start\n\t"
	 "_start:\n\t"
	 ".type _start,#function\n\t"
	 "mov	%fp, $0\n\t"
	 "ldr	%r0, [%sp]\n\t"		/* argc */
	 "add	%r1, %sp, $4\n\t"	/* argv */
	 "add	%r2, %r0, $1\n\t"	/* envp */
	 "add	%r2, %r2, %r2\n\t"
	 "add	%r2, %r2, %r2\n\t"
	 "add	%r2, %r1, %r2\n\t"
	 "bl	__platform_init\n\t"
	 "mov	%pc, %lr\n\t");
