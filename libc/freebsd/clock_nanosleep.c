#include <errno.h>
#include <time.h>

/* note on 64 bit platforms, FreeBSD timespec is the same as NetBSD,
   but this is not true on 32 bit platforms */

typedef long freebsd_time_t;

struct freebsd_timespec {
        freebsd_time_t tv_sec;
        long tv_nsec;
};

#define FREEBSD_CLOCK_REALTIME 0
#define FREEBSD_CLOCK_MONOTONIC 4 

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
