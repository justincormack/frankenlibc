#if defined(__x86_64__)
#include "x86_64/swapcontext.s"
#elif defined(__i386__)
#include "i386/swapcontext.s"
#elif defined(__ARMEL__) || defined(__ARMEB__)
#include "arm/swapcontext.s"
#elif defined(__AARCH64EL__) || defined (__AARCH64EB__)
#include "aarch64/swapcontext.s"
#elif defined(__PPC64__)
#include "ppc64/swapcontext.s"
#elif defined(__PPC__)
#include "ppc/swapcontext.s"
#else
#error "Unknown architecture"
#endif
