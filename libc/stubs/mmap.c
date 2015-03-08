#include <sys/types.h>
#include <stdlib.h>

void *_mmap(void *, size_t, int, int, int, off_t);

void *
mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{

	return _mmap(addr, length, prot, flags, fd, offset);
}
