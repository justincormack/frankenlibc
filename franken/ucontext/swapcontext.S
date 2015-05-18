#if defined(__x86_64__)
#include "x86_64/swapcontext.S"
#elif defined(__i386__)
#include "i386/swapcontext.S"
#elif defined(__ARMEL__) || defined(__ARMEB__)
#include "arm/swapcontext.S"
#elif defined(__AARCH64EL__) || defined (__AARCH64EB__)
#include "aarch64/swapcontext.S"
#elif defined(__PPC64__)
#include "powerpc64/swapcontext.S"
#elif defined(__PPC__)
#include "powerpc/swapcontext.S"
#elif defined(__MIPSEL__) || defined(__MIPSEB__)
#include "mips/swapcontext.S"
#elif defined(__riscv64)
#include "riscv64/swapcontext.S"
#else
#error "Unknown architecture"
#endif
