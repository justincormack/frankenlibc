#include <elf.h>
#include <stdint.h>

typedef __SIZE_TYPE__ size_t;

/* move to a header somewhere */
int __franken_start_main(int (*)(int,char **,char **), int, char **, char **);

#define AUX_CNT 38

size_t __hwcap;
size_t __sysinfo;
size_t __pagesize;
size_t __random;

int __platform_set_thread_area(void *);
static int64_t builtin_tls[4096/sizeof(int64_t)];

int
__libc_start_main(int (*main)(int,char **,char **), int argc, char **argv)
{
	char **envp = argv + argc + 1;

        size_t i, *auxv, aux[AUX_CNT] = { 0 };
        for (i = 0; envp[i]; i++);
        auxv = (void *)(envp + i + 1);
        for (i = 0; auxv[i]; i += 2)
		if (auxv[i] < AUX_CNT)
			aux[auxv[i]] = auxv[i + 1];
        __hwcap = aux[AT_HWCAP];
        __sysinfo = aux[AT_SYSINFO];
        __pagesize = aux[AT_PAGESZ];
	__random = aux[AT_RANDOM];

	/* init tls; gcc needs this even for some non-tls using programs */
	__platform_set_thread_area(builtin_tls);

	return __franken_start_main(main, argc, argv, envp);
}
