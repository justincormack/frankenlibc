#define TP_ADJ(p) (p)

#define ARCH_SET_FS 0x1002
#define TCGETS 0x5401

#define LINUX_MAP_SHARED        0x01
#define LINUX_MAP_PRIVATE       0x02
#define LINUX_MAP_FIXED         0x10
#define LINUX_MAP_ANON          0x20
#define LINUX_MAP_STACK         0x20000
#define LINUX_MAP_HUGETLB       0x40000
#define LINUX_MAP_HUGE_SHIFT    26
#define LINUX_MAP_HUGE_2MB      (21 << LINUX_MAP_HUGE_SHIFT)
#define LINUX_MAP_HUGE_1GB      (30 << LINUX_MAP_HUGE_SHIFT)
#define LINUX_MAP_HUGE(sz)      LINUX_MAP_HUGETLB | \
	( sz == 2097152 ? LINUX_MAP_HUGE_2MB : 0 ) | \
	( sz == 1073741824 ? LINUX_MAP_HUGE_1GB : 0 )

struct linux_stat {
	unsigned long	st_dev;
	unsigned long	st_ino;
	unsigned long	st_nlink;
	unsigned int	st_mode;
	unsigned int	st_uid;
	unsigned int	st_gid;
	unsigned int	__pad0;
	unsigned long	st_rdev;
	long		st_size;
	long		st_blksize;
	long		st_blocks;
	unsigned long	st_atime;
	unsigned long	st_atime_nsec;
	unsigned long	st_mtime;
	unsigned long	st_mtime_nsec;
	unsigned long	st_ctime;
	unsigned long	st_ctime_nsec;
	long		__unused[3];
};
