#include <lwp.h>
#include <errno.h>

lwpid_t
_lwp_self(void)
{

	errno = ENOTSUP;
	return -1;
}
