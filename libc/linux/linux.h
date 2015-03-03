#if defined(__x86_64__)
#include "x86_64/linux.h"
#elif defined(__i386__)
#include "i386/linux.h"
#elif defined(__ARMEL__) || defined(__ARMEB__)
#include "arm/linux.h"
#elif defined(__AARCH64EL__) || defined (__AARCH64EB__)
#include "aarch64/linux.h"
#elif defined(__PPC64__)
#include "ppc64/linux.h"
#elif defined(__PPC__)
#include "ppc/linux.h"
#else
#error "Unknown architecture"
#endif
