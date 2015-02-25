#include <sys/mman.h>
#include <errno.h>

int __mprotect(void *, size_t, int);

int
mprotect(void *addr, size_t length, int prot)
{
	int ret = __mprotect(addr, length, prot);
	if (ret == -1)
		errno = EINVAL;

	return ret;
}
