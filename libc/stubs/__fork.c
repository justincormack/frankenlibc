#include <unistd.h>
#include <errno.h>

pid_t fork(void);

pid_t
fork()
{

	errno = ENOTSUP;
	return -1;
}
