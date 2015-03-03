#define LINUX_CLOCK_REALTIME 0
#define LINUX_CLOCK_MONOTONIC 1

#define LINUX_MAP_SHARED	0x01
#define LINUX_MAP_PRIVATE	0x02
#define LINUX_MAP_FIXED		0x10
#define LINUX_MAP_ANON		0x20
#define LINUX_MAP_STACK		0x20000

/* note on 64 bit platforms, Linux timespec is the same as NetBSD,
   but this is not true on 32 bit platforms */

typedef long linux_time_t;

struct linux_timespec {
	linux_time_t tv_sec;
	long tv_nsec;
};

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
