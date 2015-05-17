__asm__(" \n\
.global _syscall; \n\
.type _syscall,#function; \n\
_syscall:; \n\
	svc 0; \n\
	cmp r0, #0; \n\
	bge .errnoret; \n\
	mov r1, #0; \n\
	sub r0, r1, r0; \n\
	ldr r1, =errno; \n\
	str r0, [r1]; \n\
	mov r0, #-1; \n\
.errnoret:; \n\
	mov pc, lr;");
