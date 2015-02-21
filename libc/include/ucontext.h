#if defined(__x86_64__)
#include <x86_64/ucontext.h>
#elif defined(__i386__)
#include <i386/ucontext.h>
#elif defined(__ARMEL__) || defined(__ARMEB__)
#include <arm/ucontext.h>
#elif defined(__AARCH64EL__) || defined (__AARCH64EB__)
#include <aarch64/ucontext.h>
#elif defined(__PPC64__)
#include <ppc64/ucontext.h>
#elif defined(__PPC__)
#include <ppc/ucontext.h>
#else
#error "Unknown architecture"
#endif
