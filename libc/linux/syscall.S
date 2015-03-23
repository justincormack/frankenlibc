#if defined(__x86_64__)
#include "x86_64/syscall.s"
#elif defined(__i386__)
#include "i386/syscall.s"
#elif defined(__ARMEL__) || defined(__ARMEB__)
#include "arm/syscall.s"
#elif defined(__AARCH64EL__) || defined (__AARCH64EB__)
#include "aarch64/syscall.s"
#elif defined(__PPC64__)
#include "powerpc64/syscall.s"
#elif defined(__PPC__)
#include "powerpc/syscall.s"
#elif defined(__MIPSEL__) || defined(__MIPSEB__)
#include "mips/syscall.s"
#else
#error "Unknown architecture"
#endif
