#include <fcntl.h>

#include "syscall.h"

int
fcntl(int fd, int cmd, ...)
{

	/* only support F_GETFL which has same value and return value */
	return syscall(SYS_fcntl, fd, cmd, 0);
}
