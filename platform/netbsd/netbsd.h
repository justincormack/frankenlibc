#include <stdint.h>
#include <time.h>
#include <sys/types.h>

struct netbsd_stat {
	dev_t		st_dev;
	mode_t		st_mode;
	ino_t		st_ino;
	nlink_t		st_nlink;
	uid_t		st_uid;
	gid_t		st_gid;
	dev_t		st_rdev;
	struct		timespec st_atimespec;
	struct		timespec st_mtimespec;
	struct		timespec st_ctimespec;
	struct		timespec st_birthtimespec;
	off_t		st_size;
	blkcnt_t	st_blocks;
	blksize_t	st_blksize;
	uint32_t	st_flags;
	uint32_t	st_gen;
	uint32_t	st_spare[2];
};

#define CTL_KERN 1
#define CTL_HW 6

#define KERN_OSREV 3
#define KERN_URND 61

#define HW_PAGESIZE 7

#define IOCPARM_MASK	0x1fff
#define IOCPARM_SHIFT	16
#define IOCGROUP_SHIFT	8

#define IOC_OUT		(unsigned long)0x40000000

#define _IOC(inout, group, num, len) \
    ((inout) | (((len) & IOCPARM_MASK) << IOCPARM_SHIFT) | \
    ((group) << IOCGROUP_SHIFT) | (num))

#define _IOR(g,n,t)	_IOC(IOC_OUT, (g), (n), sizeof(t))
