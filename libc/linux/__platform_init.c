#include <elf.h>

typedef __SIZE_TYPE__ size_t;

/* move to a header somewhere */
int __libc_start_main(int (*)(int,char **,char **), int, char **, char **);

#define AUX_CNT 38

size_t __platform_hwcap;
size_t __platform_sysinfo;
size_t __platform_pagesize;

int
__platform_init(int (*main)(int,char **,char **), int argc, char **argv)
{
	char **envp = argv + argc + 1;

        size_t i, *auxv, aux[AUX_CNT] = { 0 };
        for (i = 0; envp[i]; i++);
        auxv = (void *)(envp + i + 1);
        for (i = 0; auxv[i]; i += 2)
		if (auxv[i] < AUX_CNT)
			aux[auxv[i]] = auxv[i + 1];
        __platform_hwcap = aux[AT_HWCAP];
        __platform_sysinfo = aux[AT_SYSINFO];
        __platform_pagesize = aux[AT_PAGESZ];

	/* init tls */

	return __libc_start_main(main, argc, argv, envp);
}
