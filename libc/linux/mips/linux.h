#include <sys/types.h>
#include <time.h>

#define _IOC(a,b,c,d) ( ((a)<<29) | ((b)<<8) | (c) | ((d)<<16) )
#define _IOC_NONE  1U
#define _IOC_READ  2U
#define _IOC_WRITE 4U

#define _IO(a,b) _IOC(_IOC_NONE,(a),(b),0)
#define _IOW(a,b,c) _IOC(_IOC_WRITE,(a),(b),sizeof(c))
#define _IOR(a,b,c) _IOC(_IOC_READ,(a),(b),sizeof(c))
#define _IOWR(a,b,c) _IOC(_IOC_READ|_IOC_WRITE,(a),(b),sizeof(c))

#define TCGETS 0x540d

#define LINUX_MAP_SHARED        0x01
#define LINUX_MAP_PRIVATE       0x02
#define LINUX_MAP_FIXED         0x10
#define LINUX_MAP_ANON          0x0800
#define LINUX_MAP_STACK         0x40000
#define LINUX_MAP_HUGETLB       0x80000
#define LINUX_MAP_HUGE(sz)      LINUX_MAP_HUGETLB

struct linux_stat {
	unsigned long	st_dev;
	unsigned long	__st_pad0[3];
	unsigned long long	st_ino;
	mode_t		st_mode;
	nlink_t		st_nlink;
	uid_t		st_uid;
	gid_t		st_gid;
	unsigned long	st_rdev;
	unsigned long	__st_pad1[3];
	long long	st_size;
	time_t		st_atime;
	unsigned long	st_atime_nsec;
	time_t		st_mtime;
	unsigned long	st_mtime_nsec;
	time_t		st_ctime;
	unsigned long	st_ctime_nsec;
	unsigned long	st_blksize;
	unsigned long	__st_pad2;
	long long	st_blocks;
	long		__st_padding4[14];
};
