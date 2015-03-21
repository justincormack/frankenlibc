/* XXX ugly use in a macro, fix */
#define hash #

#define SYSCALL(sc, name) \
.global name; \
.type name,%function; \
name:; \
	mov	%ip, %r7; \
	ldr	%r7, =SYS_ ## sc; \
	svc	0x00000000; \
	mov	%r7, %ip; \
	cmp	%r0, hash -4096; \
	bls	.errnoret; \
	mov	%r1, hash 0; \
	sub	%r0, %r1, %r0; \
	ldr	%r1, =errno; \
	str	%r0, [%r1]; \
	mov	%r0, hash -1; \
.errnoret:; \
	mov	%pc, %lr;

#define SYSCALL_ZEROPAD

#define SYS_read			3
#define SYS_write			4
#define SYS_fstat64			197
#define SYS_mmap2			192
#define SYS_munmap			91
#define SYS_ioctl			54
#define SYS_kill			37
#define SYS_fsync			118
#define SYS_pread64			180
#define SYS_pwrite64			181
#define SYS_clock_gettime		263
#define SYS_clock_getres		264
#define SYS_clock_nanosleep		265
#define SYS_exit_group			248
#define SYS_getrandom			384
