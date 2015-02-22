.section ".note.netbsd.ident", "a"
	.p2align 2

	.long   7
	.long   4
	.long   1
	.ascii  "NetBSD\0\0"
	.long   600000000       /* requires NetBSD 6.0 */
	.previous
	.p2align 2

#if defined(__x86_64__)
#include "x86_64/crt1.s"
#elif defined(__i386__)
#include "i386/crt1.s"
#elif defined(__ARMEL__) || defined(__ARMEB__)
#include "arm/crt1.s"
#elif defined(__AARCH64EL__) || defined (__AARCH64EB__)
#include "aarch64/crt1.s"
#elif defined(__PPC64__)
#include "ppc64/crt1.s"
#elif defined(__PPC__)
#include "ppc/crt1.s"
#else
#error "Unknown architecture"
#endif
