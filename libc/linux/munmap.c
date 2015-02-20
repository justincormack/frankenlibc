#include <sys/mman.h>
#include <errno.h>

int __munmap(void *, size_t);

int
munmap(void *addr, size_t length)
{
	int ret = __munmap(addr, length);
	if (ret == -1)
		errno = EINVAL;

	return ret;
}
