#define SYSCALL(sc, name) \
.global name; \
.type name,@function; \
name:; \
	mov	$SYS_ ## sc, %eax; \
	int	$0x80; \
	jnc	_syscall_return; \
	mov	%eax, errno; \
	mov	$-1, %eax; \
_syscall_return:; \
	ret;
