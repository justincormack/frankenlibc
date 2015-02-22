#include <unistd.h>
#include <errno.h>

pid_t __fork(void);

pid_t
__fork()
{

	errno = ENOTSUP;
	return -1;
}
