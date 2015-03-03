#include <errno.h>
#include <time.h>

#include "freebsd.h"

int __platform_nanosleep(const struct freebsd_timespec *, struct freebsd_timespec *);

int
clock_nanosleep(clockid_t clockid, int flags, const struct timespec *req, struct timespec *rem)
{
	struct freebsd_timespec ftp = {req->tv_sec, req->tv_nsec};

	/* we could support these but not needed */
	if (flags != 0 || rem != NULL) {
		errno = EINVAL;
		return -1;
	}

	return __platform_nanosleep(&ftp, NULL);
}
