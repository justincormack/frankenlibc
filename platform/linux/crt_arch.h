#if defined(__x86_64__)
#include "x86_64/crt_arch.h"
#elif defined(__i386__)
#include "i386/crt_arch.h"
#elif defined(__ARMEL__) || defined(__ARMEB__)
#include "arm/crt_arch.h"
#elif defined(__AARCH64EL__) || defined (__AARCH64EB__)
#include "aarch64/crt_arch.h"
#elif defined(__PPC64__)
#include "powerpc64/crt_arch.h"
#elif defined(__PPC__)
#include "powerpc/crt_arch.h"
#elif defined(__MIPSEL__) || defined(__MIPSEB__)
#include "mips/crt_arch.h"
#else
#error "Unknown architecture"
#endif
