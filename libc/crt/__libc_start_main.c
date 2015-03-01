#include <stdint.h>

void rump_boot_setsigmodel(int) __attribute__((weak));
void rump_boot_setsigmodel(int m) {}
int rump_init(void) __attribute__((weak));
int rump_init() {}

#define RUMP_SIGMODEL_IGNORE 1

char **environ __attribute__((weak));
int errno __attribute__((weak));

static char empty_string[] = "";
char *__progname = empty_string;

void _libc_init(void) __attribute__((weak));
void _libc_init() {}

int __libc_start_main(int (*)(int,char **,char **), int, char **, char **);

void _init(void) __attribute__ ((weak));
void _init() {}
void _fini(void) __attribute__ ((weak));
void _fini() {}

extern void (*const __init_array_start)() __attribute__((weak));
extern void (*const __init_array_end)() __attribute__((weak));
extern void (*const __fini_array_start)() __attribute__((weak));
extern void (*const __fini_array_end)() __attribute__((weak));

void _exit(int) __attribute__ ((noreturn));

/* XXX if running NetBSD libc, finalizers should be set via atexit */
void exit(int) __attribute__ ((noreturn)) __attribute__((weak));
void
exit(int v)
{
	uintptr_t a = (uintptr_t)&__fini_array_end;

	for (; a>(uintptr_t)&__fini_array_start; a -= sizeof(void(*)()))
		(*(void (**)())(a - sizeof(void(*)())))();
	_fini();

	_exit(v);
}

int
__libc_start_main(int(*main)(int,char **,char **), int argc, char **argv, char **envp)
{
	uintptr_t a;

	environ = envp;

	if (argv[0]) {
		char *c;
		__progname = argv[0];
		for (c = argv[0]; *c; ++c) {
			if (*c == '/')
				__progname = c + 1;
		}
	}

	rump_boot_setsigmodel(RUMP_SIGMODEL_IGNORE);
	rump_init();

	_libc_init();

	_init();
	a = (uintptr_t)&__init_array_start;
	for (; a < (uintptr_t)&__init_array_end; a += sizeof(void(*)()))
		(*(void (**)())a)();

	exit(main(argc, argv, envp));
	return 0;
}
