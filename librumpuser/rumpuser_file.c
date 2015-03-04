#include "rumpuser_port.h"

#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>

#include <rump/rumpuser.h>

#include "rumpuser_int.h"

#include "fdinit.h"

int
rumpuser_getfileinfo(const char *path, uint64_t *sizep, int *ftp)
{

	return ENOENT;
}

int
rumpuser_open(const char *path, int ruflags, int *fdp)
{

	return EBADF;
}

int
rumpuser_close(int fd)
{

	return EBADF;
}

int
rumpuser_iovread(int fd, struct rumpuser_iovec *ruiov, size_t iovlen,
	int64_t roff, size_t *retp)
{

	return EBADF;
}

int
rumpuser_iovwrite(int fd, const struct rumpuser_iovec *ruiov, size_t iovlen,
	int64_t roff, size_t *retp)
{

	return EBADF;
}

int
rumpuser_syncfd(int fd, int flags, uint64_t start, uint64_t len)
{

	return EBADF;
}

void
rumpuser_bio(int fd, int op, void *data, size_t dlen, int64_t doff,
        rump_biodone_fn biodone, void *bioarg)
{

	biodone(bioarg, (size_t)0, EBADF);
}
