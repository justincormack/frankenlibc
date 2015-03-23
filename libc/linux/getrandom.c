#include <linux/random.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "syscall.h"

/* We use the random number that Linux passes in to all programs first,
   then we will use getrandom(), however if we have been passed in a
   descriptor to /dev/urandom we use that instead. There is a small
   chance that getrandom() is called first, and seccomp kills your
   program because it didn't allow for that, but this is very low and
   should go away once everyone has getrandom headers and a new seccomp
*/

#define PLATFORM_RND_AT 0
#define PLATFORM_RND_GR 1
#define PLATFORM_RND_FD 2

extern size_t __random;
extern int __platform_random_fd;

int __linux_randsrc = PLATFORM_RND_AT;

int
getrandom(void *buf, size_t size, unsigned int flags)
{

	switch (__linux_randsrc) {
	case PLATFORM_RND_AT:
		size = (size > sizeof(size_t)) ? sizeof(size_t) : size;
		memcpy(buf, &__random, size);
		__linux_randsrc = PLATFORM_RND_FD;
		return size;
	case PLATFORM_RND_FD:
		if (__platform_random_fd != -1)
			return read(__platform_random_fd, buf, size);

		__linux_randsrc = PLATFORM_RND_GR;
		// fallthrough
	case PLATFORM_RND_GR:
		return syscall(SYS_getrandom, buf, size, flags);
	default:
		break;
	}

	errno = ENOSYS;
	return -1;
}
