#include <lwp.h>
#include <errno.h>

int
___lwp_park60(clockid_t cklock_id, int flags, const struct timespec *ts,
	lwpid_t unpark, const void *hint, const void *unparkhint)
{

	errno = ENOTSUP;
	return -1;
}
