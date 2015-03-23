#ifndef _SYS_SYSCALL_H
#define _SYS_SYSCALL_H

#if defined(__x86_64__)
#include "../x86_64/bits/syscall.h"
#elif defined(__i386__)
#include "../i386/bits/syscall.h"
#elif defined(__ARMEL__) || defined(__ARMEB__)
#include "../arm/bits/syscall.h"
#elif defined(__AARCH64EL__) || defined (__AARCH64EB__)
#include "../aarch64/bits/syscall.h"
#elif defined(__PPC64__)
#include "../ppc64/bits/syscall.h"
#elif defined(__PPC__)
#include "../ppc/bits/syscall.h"
#elif defined(__MIPSEL__) || defined(__MIPSEB__)
#include "../mips/bits/syscall.h"
#else
#error "Unknown architecture"
#endif

#endif
