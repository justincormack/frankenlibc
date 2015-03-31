#include <sys/mman.h>
#include <errno.h>

void *_mmap(void *, size_t, int, int, int, off_t);

void *
_mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{

	if (! (fd == -1 && flags & MAP_ANON)) {
		errno = ENOSYS;
		return MAP_FAILED;
	}

	return mmap(addr, length, prot, flags, fd, offset);
}
