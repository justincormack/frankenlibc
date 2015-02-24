#if defined(__x86_64__)
#include "x86_64/crt0.c"
#elif defined(__i386__)
#include "i386/crt0.c"
#elif defined(__ARMEL__) || defined(__ARMEB__)
#include "arm/crt0.c"
#elif defined(__AARCH64EL__) || defined (__AARCH64EB__)
#include "aarch64/crt0.c"
#elif defined(__PPC64__)
#include "ppc64/crt0.c"
#elif defined(__PPC__)
#include "ppc/crt0.c"
#else
#error "Unknown architecture"
#endif

#include "__libc_start_main.c"
