#ifndef _SYS_STAT_H_
#define _SYS_STAT_H_

#include <stdint.h>
#include <time.h>
#include <sys/types.h>

struct stat {
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

#define S_IFMT   0170000

#define S_IFIFO  0010000
#define S_IFCHR  0020000
#define S_IFDIR  0040000
#define S_IFBLK  0060000
#define S_IFREG  0100000
#define S_IFLNK  0120000
#define S_IFSOCK 0140000

#define S_ISDIR(m)	(((m) & S_IFMT) == S_IFDIR)
#define S_ISCHR(m)	(((m) & S_IFMT) == S_IFCHR)
#define S_ISBLK(m)	(((m) & S_IFMT) == S_IFBLK)
#define S_ISREG(m)	(((m) & S_IFMT) == S_IFREG)
#define S_ISFIFO(m)	(((m) & S_IFMT) == S_IFIFO)
#define S_ISLNK(m)	(((m) & S_IFMT) == S_IFLNK)
#define S_ISSOCK(m)	(((m) & S_IFMT) == S_IFSOCK)

int fstat(int, struct stat *);

#endif
