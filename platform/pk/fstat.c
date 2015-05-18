#include <sys/stat.h>
#include <errno.h>

int
fstat(int fd, struct stat *st)
{

	errno = EINVAL;
	return -1;
}
