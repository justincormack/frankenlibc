#define TCGETS 0x5401

struct linux_stat {
	unsigned long long	st_dev;
	unsigned long long	st_ino;
	unsigned int		st_mode;
	unsigned int		st_nlink;
	unsigned int		st_uid;
	unsigned int		st_gid;
	unsigned long long	st_rdev;
	unsigned long long	__pad1;
	long long		st_size;
	int			st_blksize;
	int			__pad2;
	long long		st_blocks;
	int			st_atime;
	unsigned int		st_atime_nsec;
	int			st_mtime;
	unsigned int		st_mtime_nsec;
	int			st_ctime;
	unsigned int		st_ctime_nsec;
	unsigned int		__unused4;
	unsigned int		__unused5;
};
