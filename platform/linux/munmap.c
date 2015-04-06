#include <sys/mman.h>
#include <errno.h>

#include "syscall.h"

int
munmap(void *addr, size_t length)
{
	int ret = syscall(SYS_munmap, addr, length);

	if (ret == -1)
		errno = EINVAL;

	return ret;
}
