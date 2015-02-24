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

#define SYSCALL_MMAP(sc, name) \
.global name; \
.type name,@function; \
name:; \
	mov	$0, %r9; \
	mov	$SYS_mmap, %rax; \
	mov	%rcx, %r10; \
	syscall; \
	jnc	_syscall_return; \
	mov	%rax, errno; \
	mov	$-1, %rax; \
_syscall_return:; \
	ret
