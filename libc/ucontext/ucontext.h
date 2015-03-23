#ifndef _UCONTEXT_H
#define _UCONTEXT_H

#include <stdlib.h>

#include <rename.h>

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
#else
#error "Unknown architecture"
#endif

/* Note the type of makecontext is not the standard, as this is
   not valid C. We only allow a single void* argument but define
   as if it takes no arguments as that is normal.
*/
int  getcontext(ucontext_t *);
void makecontext(ucontext_t *, void (*)(void), int, void *);
int  swapcontext(ucontext_t *, ucontext_t *);

#endif
