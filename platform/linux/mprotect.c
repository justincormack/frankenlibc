#include <sys/mman.h>
#include <errno.h>

#include "syscall.h"

int
mprotect(void *addr, size_t length, int prot)
{
	int ret = syscall(SYS_mprotect, addr, length, prot);

	if (ret == -1)
		errno = EINVAL;

	return ret;
}
