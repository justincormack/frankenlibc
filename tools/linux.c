#include <seccomp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <asm/prctl.h>
#include <sys/prctl.h>
#include <sys/ioctl.h>
#include <sys/syscall.h>

scmp_filter_ctx ctx;

int
filter_init(char *program)
{
	int ret, i;

	ctx = seccomp_init(SCMP_ACT_KILL);
	if (ctx == NULL)
		return -1;

	/* arch_prctl(ARCH_SET_FS, x) */
#ifdef __NR_arch_prctl
	ret = seccomp_rule_add(ctx, SCMP_ACT_ALLOW,
		SCMP_SYS(arch_prctl), 1, SCMP_A0(SCMP_CMP_EQ, ARCH_SET_FS));
	if (ret < 0) return ret;
#endif

	/* exit(x) */
	ret = seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit), 0);
	if (ret < 0) return ret;

	/* exit_group(x) */
	ret = seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit_group), 0);
	if (ret < 0) return ret;

	/* clock_gettime(x, y) */
	ret = seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(clock_gettime), 0);
	if (ret < 0) return ret;

	/* clock_getres(x, y) */
	ret = seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(clock_getres), 0);
	if (ret < 0) return ret;

	/* clock_nanosleep(w, x, y, z) */
	ret = seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(clock_nanosleep), 0);
	if (ret < 0) return ret;

	/* getrandom(x, y, z) */
#ifdef __NR_getrandom 
	ret = seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(getrandom), 0);
	if (ret < 0) return ret;
#else
	{
		int fd = open("/dev/urandom", O_RDONLY);

		if (fd == -1) return -1;
		ret = seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(read), 1,
			SCMP_A0(SCMP_CMP_EQ, fd));
		if (ret < 0) return ret;
	}
#endif

	/* kill(0, SIGABRT) */
	ret = seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(kill), 2,
		SCMP_A0(SCMP_CMP_EQ, 0), SCMP_A1(SCMP_CMP_EQ, SIGABRT));
	if (ret < 0) return ret;

	/* mmap(a, b, c, d, -1, e) */
#ifdef __NR_mmap2
	ret = seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(mmap2), 0);
#else
	ret = seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(mmap), 0);
#endif
	if (ret < 0) return ret;

	/* mprotext(a, b, c) XXX allow disable exec */
	ret = seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(mprotect), 0);
	if (ret < 0) return ret;

	/* munmap(a, b) */
	ret = seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(munmap), 0);
	if (ret < 0) return ret;

	/* fstat(a, b) as used to check for existence */
#ifdef __NR_fstat64
	ret = seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(fstat64), 0);
#else
	ret = seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(fstat), 0);
#endif
	if (ret < 0) return ret;

	return 0;
}

int
filter_fd(int fd, int flags, mode_t mode)
{
	int ret;

	/* read(fd, x, y) */
	if (flags == O_RDONLY || flags == O_RDWR) {
		ret = seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(read), 1,
			SCMP_A0(SCMP_CMP_EQ, fd));
		if (ret < 0) return ret;
	}

	/* write(fd, x, y) */
	if (flags == O_WRONLY || flags == O_RDWR) {
		ret = seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(write), 1,
			SCMP_A0(SCMP_CMP_EQ, fd));
		if (ret < 0) return ret;
	}

	/* ioctl(fd, TCGETS, x) */
	ret = seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(ioctl), 2,
		SCMP_A0(SCMP_CMP_EQ, fd), SCMP_A1(SCMP_CMP_EQ, TCGETS));

	return 0;
}

int
filter_load_exec(char *program, char **argv, char **envp)
{
	int ret;
#ifdef NR_execveat
	int fd = open(program, O_RDONLY | O_CLOEXEC);

	if (fd == -1) {
		perror("open");
		exit(1);
	}
#endif

	/* seccomp_export_pfc(ctx, 1); */

	/* only working fexecve using execveat really safe
	   but this is not widely available yet */
#ifndef NR_execveat
	ret = seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(execve), 0);
	if (ret < 0) return ret;
#else
	/* lock down execveat to just the one we need to exec program */
	ret = seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(execveat), 2
		SCMP_A0(SCMP_CMP_EQ, fd), SCMP_A5(SCMP_CMP_EQ, AT_EMPTY_PATH));
#endif

	ret = seccomp_load(ctx);
	if (ret < 0) return ret;

	seccomp_release(ctx);

#ifndef NR_execveat
	if (execve(program, argv, envp) == -1) {
		perror("execve");
		exit(1);
	}
#else
	if (execveat(fd, "", argv, envp, AT_EMPTY_PATH) == -1) {
		perror("execveat");
		exit(1);
	}
#endif

	return 0;
}
