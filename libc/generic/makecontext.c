#if defined(__x86_64__)
#include "x86_64/makecontext.c"
#elif defined(__i386__)
#include "i386/makecontext.c"
#elif defined(__ARMEL__) || defined(__ARMEB__)
#include "arm/makecontext.c"
#elif defined(__AARCH64EL__) || defined (__AARCH64EB__)
#include "aarch64/makecontext.c"
#elif defined(__PPC64__)
#include "ppc64/makecontext.c"
#elif defined(__PPC__)
#include "ppc/makecontext.c"
#else
#error "Unknown architecture"
#endif
