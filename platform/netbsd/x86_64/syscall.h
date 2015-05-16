#define SYSCALL(sc, name) \
.global name; \
.type name,@function; \
name:; \
	mov	$SYS_ ## sc, %rax; \
	mov	%rcx, %r10; \
	syscall; \
	jnc	_syscall_return ## sc; \
	mov	%rax, errno; \
	mov	$-1, %rax; \
_syscall_return ## sc:; \
	ret;

#define SYSCALL6(sc, name) \
.global name; \
.type name,@function; \
name:; \
	sub	$0x10, %rsp; \
	mov	%r9, 0x8(%rsp); \
	mov	$0, %r9; \
	mov	$SYS_ ## sc, %rax; \
	mov	%rcx, %r10; \
	syscall; \
	jnc	_syscall_return ## sc; \
	mov	%rax, errno; \
	mov	$-1, %rax; \
_syscall_return ## sc:; \
	add	$0x10, %rsp; \
	ret
