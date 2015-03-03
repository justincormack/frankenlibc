#define SYSCALL(sc, name) \
.global name; \
.type name,@function; \
name:; \
	mov	$SYS_ ## sc, %rax; \
	mov	%rcx, %r10; \
	syscall; \
	jnc	_syscall_return; \
	mov	%rax, errno; \
	mov	$-1, %rax; \
_syscall_return:; \
	ret;
