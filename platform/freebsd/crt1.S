	.section ".note.ABI-tag", "a"
	.p2align 2
	.long 1f - 0f
	.long 3f - 2f
	.long  1
0:	.asciz "FreeBSD"
1:	.p2align 2
2:	.long 900000
3:	.p2align 2
	.text

#if defined(__x86_64__)
#include "x86_64/crt1.S"
#elif defined(__i386__)
#include "i386/crt1.S"
#elif defined(__ARMEL__) || defined(__ARMEB__)
#include "arm/crt1.S"
#elif defined(__AARCH64EL__) || defined (__AARCH64EB__)
#include "aarch64/crt1.S"
#elif defined(__PPC64__)
#include "ppc64/crt1.S"
#elif defined(__PPC__)
#include "ppc/crt1.S"
#else
#error "Unknown architecture"
#endif
