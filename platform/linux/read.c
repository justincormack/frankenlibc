#include <unistd.h>

#include <sys/syscall.h>
#include "syscall.h"

ssize_t
read(int fd, void *buf, size_t count)
{

	return syscall(SYS_read, fd, buf, count);
}
