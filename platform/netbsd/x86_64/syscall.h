#define xstr(s) str(s)
#define str(s) #s

#define SYSCALL(sc, name) \
__asm__( " \n\
.global " #name "; \n\
.type " #name ",@function; \n\
" #name ":; \n\
	mov	$" xstr(SYS_ ## sc) ", %rax; \n\
	mov	%rcx, %r10; \n\
	syscall; \n\
	jnc	" xstr(_syscall_return_ ## sc) "; \n\
	mov	%rax, errno; \n\
	mov	$-1, %rax; \n\
" xstr(_syscall_return_ ## sc) ":; \n\
	ret; \n\
");

#define SYSCALL6(sc, name) \
__asm__( "\n\
.global " #name "; \n\
.type " #name ",@function; \n\
" #name ":; \n\
	sub	$0x10, %rsp; \n\
	mov	%r9, 0x8(%rsp); \n\
	mov	$0, %r9; \n\
	mov	$" xstr(SYS_ ## sc) ", %rax; \n\
	mov	%rcx, %r10; \n\
	syscall; \n\
	jnc	" xstr(_syscall_return_ ## sc) "; \n\
	mov	%rax, errno; \n\
	mov	$-1, %rax; \n\
" xstr(_syscall_return_ ## sc) ":; \n\
	add	$0x10, %rsp; \n\
	ret; \n\
");
