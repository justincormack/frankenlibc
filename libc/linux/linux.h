#define LINUX_CLOCK_REALTIME 0
#define LINUX_CLOCK_MONOTONIC 1

#define LINUX_MAP_SHARED	0x01
#define LINUX_MAP_PRIVATE	0x02
#define LINUX_MAP_FIXED		0x10
#define LINUX_MAP_ANON		0x20
/* XXX may vary by arch */
#define LINUX_MAP_STACK		0x20000

#define LINUX_S_IFMT   0170000

#define LINUX_S_IFDIR  0040000
#define LINUX_S_IFCHR  0020000
#define LINUX_S_IFBLK  0060000
#define LINUX_S_IFREG  0100000
#define LINUX_S_IFIFO  0010000
#define LINUX_S_IFLNK  0120000
#define LINUX_S_IFSOCK 0140000

#define LINUX_S_ISDIR(mode)  (((mode) & LINUX_S_IFMT) == LINUX_S_IFDIR)
#define LINUX_S_ISCHR(mode)  (((mode) & LINUX_S_IFMT) == LINUX_S_IFCHR)
#define LINUX_S_ISBLK(mode)  (((mode) & LINUX_S_IFMT) == LINUX_S_IFBLK)
#define LINUX_S_ISREG(mode)  (((mode) & LINUX_S_IFMT) == LINUX_S_IFREG)
#define LINUX_S_ISFIFO(mode) (((mode) & LINUX_S_IFMT) == LINUX_S_IFIFO)
#define LINUX_S_ISLNK(mode)  (((mode) & LINUX_S_IFMT) == LINUX_S_IFLNK)
#define LINUX_S_ISSOCK(mode) (((mode) & LINUX_S_IFMT) == LINUX_S_IFSOCK)

#define linux_makedev(x, y) ( \
	(((x) & 0xfffff000ULL) << 32) | \
	(((x) & 0x00000fffULL) <<  8) | \
	(((y) & 0xffffff00ULL) << 12) | \
	(((y) & 0x000000ffULL)) )

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
