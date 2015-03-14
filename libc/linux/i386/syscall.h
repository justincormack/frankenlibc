#define SYSCALL(sc, name) \
.global name; \
.type name,@function; \
name:; \
	mov	$SYS_ ## sc, %eax; \
	push	%ebx; \
	push	%esi; \
	push	%edi; \
	push	%ebp; \
	mov	0x14(%esp), %ebx; \
	mov	0x18(%esp), %ecx; \
	mov	0x1c(%esp), %edx; \
	mov	0x20(%esp), %esi; \
	mov	0x24(%esp), %edi; \
	mov	0x28(%esp), %ebp; \
	int	$0x80; \
	pop	%ebp; \
	pop	%edi; \
	pop	%esi; \
	pop	%ebx; \
.errno:; \
	cmp	$-4095, %eax; \
	jbe	.errnoret; \
	neg	%eax; \
	mov	%eax, errno; \
	mov	$-1, %eax; \
.errnoret:; \
	ret;

#define SYS_read			3
#define SYS_write			4
#define SYS_fstat64			197
#define SYS_mmap2			192
#define SYS_munmap			91
#define SYS_ioctl			54
#define SYS_kill			37
#define SYS_clock_gettime		265
#define SYS_clock_getres		266
#define SYS_clock_nanosleep		267
#define SYS_exit_group			252
#define SYS_getrandom			355
