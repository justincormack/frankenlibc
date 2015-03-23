#include <sys/types.h>
#include <time.h>

#define TCGETS 0x540d

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
