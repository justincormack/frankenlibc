#include <unistd.h>

ssize_t
write(int fd, const void *buf, size_t count)
{

	/* no console yet */

	return count;
}
