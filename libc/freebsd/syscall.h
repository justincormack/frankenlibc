#if defined(__x86_64__)
#include "x86_64/syscall.h"
#elif defined(__i386__)
#include "i386/syscall.h"
#elif defined(__ARMEL__) || defined(__ARMEB__)
#include "arm/syscall.h"
#elif defined(__AARCH64EL__) || defined (__AARCH64EB__)
#include "aarch64/syscall.h"
#elif defined(__PPC64__)
#include "ppc64/syscall.h"
#elif defined(__PPC__)
#include "ppc/syscall.h"
#else
#error "Unknown architecture"
#endif

#define SYS_read			3
#define SYS_write			4
#define	SYS_fstat			189
#define SYS_mmap			477
#define SYS_munmap			73
#define SYS_ioctl			54
#define SYS_kill			37
#define SYS_clock_gettime		232
#define SYS_clock_getres		234
#define SYS_exit			1
#define SYS___sysctl			202
#define SYS_nanosleep			240	
