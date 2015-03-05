#include <linux/random.h>
#include <errno.h>
#include <string.h>

extern size_t __platform_random;

#define RND_AT 0
#define RND_GR 1

static int __linux_randsrc = RND_AT;

int __getrandom(void *, size_t, unsigned int);

int
getrandom(void *buf, size_t size, unsigned int flags)
{

	switch (__linux_randsrc) {
	case RND_AT:
		size = (size > sizeof(size_t)) ? sizeof(size_t) : size;
		memcpy(buf, &__platform_random, size);
		__linux_randsrc = RND_GR;
		return size;
	case RND_GR:
		return __getrandom(buf, size, flags);
	default:
		break;
	}

	errno = ENOSYS;
	return -1;
}
