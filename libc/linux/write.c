#include <unistd.h>

#include "syscall.h"

ssize_t
write(int fd, const void *buf, size_t count)
{

	return syscall(SYS_write, fd, buf, count);
}
