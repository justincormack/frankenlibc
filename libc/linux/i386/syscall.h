#define SYSCALL(sc, name) \
.global name; \
.type name,@function; \
name:; \
	mov	$SYS_ ## sc, %eax; \
	push	%ebx; \
	push	%esi; \
	push	%edi; \
	mov	0x10(%esp), %ebx; \
	mov	0x14(%esp), %ecx; \
	mov	0x18(%esp), %edx; \
	mov	0x1c(%esp), %esi; \
	mov	0x20(%esp), %edi; \
	int	$0x80; \
	pop	%edi; \
	pop	%esi; \
	pop	%ebx; \
.errno:; \
	cmp	$0, %eax; \
	jge	.errnoret; \
	neg	%eax; \
	mov	%eax, errno; \
	mov	$-1, %eax; \
.errnoret:; \
	ret;

#define SYS_write			4
#define SYS_mmap2			192
#define SYS_munmap			91
#define SYS_kill			37
#define SYS_clock_gettime		265
#define SYS_clock_nanosleep		267
#define SYS_exit_group			252
#define SYS_getrandom			355
