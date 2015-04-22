#include <sys/types.h>

#define LINUX_EAGAIN	11

#define LINUX_CLOCK_REALTIME 0
#define LINUX_CLOCK_MONOTONIC 1

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

#define	IFNAMSIZ	16

typedef unsigned short sa_family_t;

struct sockaddr
{
	sa_family_t sa_family;
	char sa_data[14];
};

struct ifmap {
	unsigned long int mem_start;
	unsigned long int mem_end;
	unsigned short int base_addr;
	unsigned char irq;
	unsigned char dma;
	unsigned char port;
};

#define IFHWADDRLEN	6

struct ifreq {
	union
	{
		char	ifrn_name[IFNAMSIZ];		/* if name, e.g. "en0" */
	} ifr_ifrn;
	
	union {
		struct	sockaddr ifru_addr;
		struct	sockaddr ifru_dstaddr;
		struct	sockaddr ifru_broadaddr;
		struct	sockaddr ifru_netmask;
		struct  sockaddr ifru_hwaddr;
		short	ifru_flags;
		int	ifru_ivalue;
		int	ifru_mtu;
		struct  ifmap ifru_map;
		char	ifru_slave[IFNAMSIZ];	/* Just fits the size */
		char	ifru_newname[IFNAMSIZ];
		void *	ifru_data;
	} ifr_ifru;
};

#define ifr_name	ifr_ifrn.ifrn_name	/* interface name 	*/
#define ifr_hwaddr	ifr_ifru.ifru_hwaddr	/* MAC address 		*/
#define	ifr_addr	ifr_ifru.ifru_addr	/* address		*/
#define	ifr_dstaddr	ifr_ifru.ifru_dstaddr	/* other end of p-p lnk	*/
#define	ifr_broadaddr	ifr_ifru.ifru_broadaddr	/* broadcast address	*/
#define	ifr_netmask	ifr_ifru.ifru_netmask	/* interface net mask	*/
#define	ifr_flags	ifr_ifru.ifru_flags	/* flags		*/
#define	ifr_metric	ifr_ifru.ifru_ivalue	/* metric		*/
#define	ifr_mtu		ifr_ifru.ifru_mtu	/* mtu			*/
#define ifr_map		ifr_ifru.ifru_map	/* device map		*/
#define ifr_slave	ifr_ifru.ifru_slave	/* slave device		*/
#define	ifr_data	ifr_ifru.ifru_data	/* for use by interface	*/
#define ifr_ifindex	ifr_ifru.ifru_ivalue	/* interface index	*/
#define ifr_bandwidth	ifr_ifru.ifru_ivalue    /* link bandwidth	*/
#define ifr_qlen	ifr_ifru.ifru_ivalue	/* Queue length 	*/
#define ifr_newname	ifr_ifru.ifru_newname	/* New name		*/

#if defined(__x86_64__)
#include "x86_64/linux.h"
#elif defined(__i386__)
#include "i386/linux.h"
#elif defined(__ARMEL__) || defined(__ARMEB__)
#include "arm/linux.h"
#elif defined(__AARCH64EL__) || defined (__AARCH64EB__)
#include "aarch64/linux.h"
#elif defined(__PPC64__)
#include "powerpc64/linux.h"
#elif defined(__PPC__)
#include "powerpc/linux.h"
#elif defined(__MIPSEL__) || defined(__MIPSEB__)
#include "mips/linux.h"
#else
#error "Unknown architecture"
#endif

#define BLKGETSIZE64	_IOR(0x12, 114, size_t)
#define TUNGETIFF	_IOR('T', 210, unsigned int)
