#include <stdint.h>
#include <sys/types.h>

#define CTL_KERN 1
#define CTL_HW 6

#define KERN_ARND 37

#define HW_PAGESIZE 7

/* note on 64 bit platforms, FreeBSD timespec is the same as NetBSD,
   but this is not true on 32 bit platforms */

typedef long freebsd_time_t;

struct freebsd_timespec {
	freebsd_time_t tv_sec;
	long tv_nsec;
};

#define FREEBSD_CLOCK_REALTIME 0
#define FREEBSD_CLOCK_MONOTONIC 4 

#define IOCPARM_SHIFT	13
#define IOCPARM_MASK	((1 << IOCPARM_SHIFT) - 1)
#define IOC_OUT		0x40000000

#define _IOC(inout,group,num,len)       ((unsigned long) \
	((inout) | (((len) & IOCPARM_MASK) << 16) | ((group) << 8) | (num)))

#define _IOR(g,n,t)	_IOC(IOC_OUT, (g), (n), sizeof(t))

#define	DIOCGMEDIASIZE	_IOR('d', 129, off_t)

#define FREEBSD_S_IFMT   0170000

#define FREEBSD_S_IFIFO  0010000
#define FREEBSD_S_IFCHR  0020000
#define FREEBSD_S_IFDIR  0040000
#define FREEBSD_S_IFBLK  0060000
#define FREEBSD_S_IFREG  0100000
#define FREEBSD_S_IFLNK  0120000
#define FREEBSD_S_IFSOCK 0140000

#define FREEBSD_S_ISDIR(mode)  (((mode) & FREEBSD_S_IFMT) == FREEBSD_S_IFDIR)
#define FREEBSD_S_ISCHR(mode)  (((mode) & FREEBSD_S_IFMT) == FREEBSD_S_IFCHR)
#define FREEBSD_S_ISBLK(mode)  (((mode) & FREEBSD_S_IFMT) == FREEBSD_S_IFBLK)
#define FREEBSD_S_ISREG(mode)  (((mode) & FREEBSD_S_IFMT) == FREEBSD_S_IFREG)
#define FREEBSD_S_ISFIFO(mode) (((mode) & FREEBSD_S_IFMT) == FREEBSD_S_IFIFO)
#define FREEBSD_S_ISLNK(mode)  (((mode) & FREEBSD_S_IFMT) == FREEBSD_S_IFLNK)
#define FREEBSD_S_ISSOCK(mode) (((mode) & FREEBSD_S_IFMT) == FREEBSD_S_IFSOCK)

typedef uint32_t freebsd_dev_t;
typedef uint32_t freebsd_ino_t;
typedef uint16_t freebsd_mode_t;
typedef uint16_t freebsd_nlink_t;
typedef int64_t  freebsd_blkcnt_t;
typedef uint32_t freebsd_blksize_t;
typedef uint32_t freebsd_fflags_t;

struct freebsd_stat {
  freebsd_dev_t			st_dev;
  freebsd_ino_t			st_ino;
  freebsd_mode_t		st_mode;
  freebsd_nlink_t		st_nlink;
  uid_t				st_uid;
  gid_t				st_gid;
  freebsd_dev_t			st_rdev;
  struct freebsd_timespec	st_atim;
  struct freebsd_timespec	st_mtim;
  struct freebsd_timespec	st_ctim;
  off_t				st_size;
  freebsd_blkcnt_t		st_blocks;
  freebsd_blksize_t		st_blksize;
  freebsd_fflags_t		st_flags;
  uint32_t			st_gen;
  int32_t			st_lspare;
  struct freebsd_timespec	st_birthtim;
  unsigned int :(8 / 2) * (16 - (int)sizeof(struct freebsd_timespec));
  unsigned int :(8 / 2) * (16 - (int)sizeof(struct freebsd_timespec));
};
