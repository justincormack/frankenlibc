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
