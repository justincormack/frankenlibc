#if _CALL_ELF == 2
#error "powerpc64le elf ABI v2 not supported yet"
#endif

__asm__("\
.text \n\
	.global _start \n\
	.section \".opd\",\"aw\" \n\
	.align 3 \n\
_start: \n\
	.quad ._start,.TOC.@tocbase,0 \n\
	.previous \n\
	.global ._start \n\
._start: \n\
	mr 3, 1 \n\
	clrrdi 1, 1, 4 \n\
	li 0, 0 \n\
	stdu 1, -128(1) \n\
	mtlr 0 \n\
	std 0, 0(1) \n\
	bl __cstart \n\
	nop \n\
");
