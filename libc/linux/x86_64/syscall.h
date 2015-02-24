#define SYSCALL(sc, name) \
.global name; \
.type name,@function; \
name:; \
	mov	$SYS_ ## sc, %rax; \
	mov	%rcx, %r10; \
	syscall; \
	cmpq	$-4095, %rax; \
	jbe	_syscall_return; \
	neg	%rax; \
	mov	%rax, errno; \
	mov	$-1, %rax; \
_syscall_return:; \
	ret;

#define SYS_write			1
#define SYS_mmap			9
#define SYS_munmap			11
#define SYS_ioctl			16
#define SYS_kill			62
#define SYS_clock_gettime		228
#define SYS_clock_nanosleep		230
#define SYS_exit_group			231
#define SYS_getrandom			318
