#include <sys/mman.h>
#include <errno.h>

void *
_mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{

	if (! (fd == -1 && flags & MAP_ANON)) {
		errno = ENOSYS;
		return MAP_FAILED;
	}

	return mmap(addr, length, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, fd, offset);
}
