#ifndef _UCONTEXT_H
#define _UCONTEXT_H

#include <stdlib.h>

#if defined(__x86_64__)
#include <x86_64/ucontext.h>
#elif defined(__i386__)
#include <i386/ucontext.h>
#elif defined(__ARMEL__) || defined(__ARMEB__)
#include <arm/ucontext.h>
#elif defined(__AARCH64EL__) || defined (__AARCH64EB__)
#include <aarch64/ucontext.h>
#elif defined(__PPC64__)
#include <powerpc64/ucontext.h>
#elif defined(__PPC__)
#include <powerpc/ucontext.h>
#elif defined(__MIPSEL__) || defined(__MIPSEB__)
#include <mips/ucontext.h>
#elif defined(__riscv64)
#include "riscv64/ucontext.h"
#else
#error "Unknown architecture"
#endif

#define getcontext(c) __franken_getcontext(c)
#define makecontext(c, f, i, a) __franken_makecontext(c, f, i, a)
#define swapcontext(c1, c2) __franken_swapcontext(c1, c2)

/* Note the type of makecontext is not the standard, as this is
   not valid C. We only allow a single void* argument but define
   as if it takes no arguments as that is normal.
*/
int  getcontext(ucontext_t *);
void makecontext(ucontext_t *, void (*)(void), int, void *);
int  swapcontext(ucontext_t *, ucontext_t *);

#endif
