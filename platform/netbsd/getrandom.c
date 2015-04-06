#include <linux/random.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>

#include "netbsd.h"

int __platform_sysctl(const int *, unsigned int, void *, size_t *, const void *, size_t);

int
getrandom(void *buf, size_t size, unsigned int flags)
{
	const int ctl[2] = {CTL_KERN, KERN_URND};
	char rand[4];
	size_t lenp = sizeof(int);
	int res;

	res = __platform_sysctl(ctl, 2, rand, &lenp, NULL, 0);
	if (res == -1)
		return -1;
	if (lenp != sizeof(int)) {
		errno = ENOSYS;
		return -1;
	}
	size = size > lenp ? lenp : size;
	memcpy(buf, rand, size);

	return size;
}
