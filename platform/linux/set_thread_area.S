#if defined(__x86_64__)
#include "x86_64/__set_thread_area.s"
#elif defined(__i386__)
#include "i386/__set_thread_area.s"
#elif defined(__ARMEL__) || defined(__ARMEB__)
#include "arm/__set_thread_area.s"
#elif defined(__AARCH64EL__) || defined (__AARCH64EB__)
#include "aarch64/__set_thread_area.s"
#elif defined(__PPC64__)
#include "powerpc64/__set_thread_area.s"
#elif defined(__PPC__)
#include "powerpc/__set_thread_area.s"
#elif defined(__MIPSEL__) || defined(__MIPSEB__)
#include "mips/__set_thread_area.s"
#else
#error "Unknown architecture"
#endif
