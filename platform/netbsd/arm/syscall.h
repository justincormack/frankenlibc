#define SYSCALL(sc, name) \
.global name; \
.type name,#function; \
name:; \
	mov ip,r7; \
	ldr r7, =SYS_ ## sc; \
	svc 0; \
	mov r7, ip; \
	cmp r0, #0; \
	bge .errnoret ## sc; \
	mov r1, #0; \
	sub r0, r1, r0; \
	ldr r1, =errno; \
	str r0, [r1]; \
	mov r0, #-1; \
.errnoret ## sc:; \
	mov pc, lr;
