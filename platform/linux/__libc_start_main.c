#include <elf.h>
#include <stdint.h>

#include "linux.h"

#ifndef TP_ADJ
#define TP_ADJ(p) (p)
#endif

/* move to a header somewhere */
int __franken_start_main(int (*)(int,char **,char **), int, char **, char **);

int __libc_start_main(int (*)(int,char **,char **), int, char **);

#define AUX_CNT 38

size_t *__auxv;
size_t __hwcap;
size_t __sysinfo;
size_t __pagesize;
size_t __random;

int __set_thread_area(void *);
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
	__auxv = auxv;
	__hwcap = aux[AT_HWCAP];
	__sysinfo = aux[AT_SYSINFO];
	__pagesize = aux[AT_PAGESZ];
	__random = aux[AT_RANDOM];

	/* init tls; gcc needs this even for some non-tls using programs */
	/* XXX will do properly soon */
	__set_thread_area(TP_ADJ(builtin_tls));

	return __franken_start_main(main, argc, argv, envp);
}
