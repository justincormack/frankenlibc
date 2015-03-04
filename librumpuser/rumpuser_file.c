#include "rumpuser_port.h"

#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include <rump/rumpuser.h>

#include "rumpuser_int.h"

int
rumpuser_getfileinfo(const char *path, uint64_t *sizep, int *ftp)
{
	struct stat st;
	int fd;
	int ret;
	int ft;

	memset(&st, 0, sizeof(struct stat));

	fd = atoi(path);
	ret = fstat(fd, &st);
	if (ret == -1)
		ET(EBADF);	

	if (sizep)
		*sizep = st.st_size;

	switch (st.st_mode & S_IFMT) {
	case S_IFDIR:
		ft = RUMPUSER_FT_DIR;
		break;
	case S_IFREG:
		ft = RUMPUSER_FT_REG;
		break;
	case S_IFBLK:
		ft = RUMPUSER_FT_BLK;
		break;
	case S_IFCHR:
		ft = RUMPUSER_FT_CHR;
		break;
	default:
		ft = RUMPUSER_FT_OTHER;
		break;
	}

	if (ftp)
		*ftp = ft;

	return 0;	
}

int
rumpuser_open(const char *path, int ruflags, int *fdp)
{

	ET(ENOENT);
}

int
rumpuser_close(int fd)
{

	ET(EBADF);
}

int
rumpuser_iovread(int fd, struct rumpuser_iovec *ruiov, size_t iovlen,
	int64_t roff, size_t *retp)
{

	ET(EBADF);
}

int
rumpuser_iovwrite(int fd, const struct rumpuser_iovec *ruiov, size_t iovlen,
	int64_t roff, size_t *retp)
{

	ET(EBADF);
}

int
rumpuser_syncfd(int fd, int flags, uint64_t start, uint64_t len)
{

	ET(EBADF);
}

void
rumpuser_bio(int fd, int op, void *data, size_t dlen, int64_t doff,
        rump_biodone_fn biodone, void *bioarg)
{

	biodone(bioarg, (size_t)0, EBADF); /* convert error no */
}
