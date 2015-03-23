#define TCGETS 0x5401

#define LINUX_MAP_SHARED        0x01
#define LINUX_MAP_PRIVATE       0x02
#define LINUX_MAP_FIXED         0x10
#define LINUX_MAP_ANON          0x20
#define LINUX_MAP_STACK         0x20000
#define LINUX_MAP_HUGETLB       0x40000
#define LINUX_MAP_HUGE_SHIFT    26
#define LINUX_MAP_HUGE_64KB	(16 << LINUX_MAP_HUGE_SHIFT)
#define LINUX_MAP_HUGE_1MB	(20 << LINUX_MAP_HUGE_SHIFT)
#define LINUX_MAP_HUGE_16MB	(24 << LINUX_MAP_HUGE_SHIFT)
#define LINUX_MAP_HUGE(sz)      LINUX_MAP_HUGETLB | \
	( sz == 65536 ? LINUX_MAP_HUGE_64KB : 0 ) | \
	( sz == 1048576 ? LINUX_MAP_HUGE_1MB : 0 ) | \
	( sz == 16777216 ? LINUX_MAP_HUGE_16MB : 0 )

struct linux_stat {
	unsigned long long	st_dev;
	unsigned char		__pad0[4];
	unsigned long		__st_ino;
	unsigned int		st_mode;
	unsigned int		st_nlink;
	unsigned long		st_uid;
	unsigned long		st_gid;
	unsigned long long	st_rdev;
	unsigned char		__pad3[4];
	long long		st_size;
	unsigned long		st_blksize;
	unsigned long long	st_blocks;
	unsigned long		st_atime;
	unsigned long		st_atime_nsec;
	unsigned long		st_mtime;
	unsigned int		st_mtime_nsec;
	unsigned long		st_ctime;
	unsigned long		st_ctime_nsec;
	unsigned long long	st_ino;
};
