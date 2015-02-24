__asm__ (".section \".note.netbsd.ident\", \"a\"\n\t"
	 ".p2align 2\n\t"

	 ".long   7\n\t"
	 ".long   4\n\t"
	 ".long   1\n\t"
	 ".ascii  \"NetBSD\0\0\"\n\t"
	 ".long   600000000\n\t"       /* requires NetBSD 6.0 */
	 ".previous\n\t"
	 ".p2align 2\n\t");

#if defined(__x86_64__)
#include "x86_64/crt1.c"
#elif defined(__i386__)
#include "i386/crt1.c"
#elif defined(__ARMEL__) || defined(__ARMEB__)
#include "arm/crt1.c"
#elif defined(__AARCH64EL__) || defined (__AARCH64EB__)
#include "aarch64/crt1.c"
#elif defined(__PPC64__)
#include "ppc64/crt1.c"
#elif defined(__PPC__)
#include "ppc/crt1.c"
#else
#error "Unknown architecture"
#endif

#include "__libc_start_main.c"
