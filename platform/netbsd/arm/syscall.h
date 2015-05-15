#define SYSCALL(sc, name) \
.global name; \
.type name,@function; \
name:; \
	mov ip,r7; \
	ldr r7, =SYS_ ## name; \
	svc 0; \
	mov r7, ip; \
	cmp r0, #0; \
	bge .errnoret; \
	mov r1, #0; \
	sub r0, r1, r0; \
	ldr r1, =errno; \
	str r0, [r1]; \
	mov r0, #-1; \
.errnoret:; \
	mov pc, lr;\
