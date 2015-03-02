#include <time.h>
#include <errno.h>

#define LINUX_CLOCK_REALTIME 0
#define LINUX_CLOCK_MONOTONIC 1

/* note on 64 bit platforms, Linux timespec is the same as NetBSD,
   but this is not true on 32 bit platforms */

typedef long linux_time_t;

struct linux_timespec {
	linux_time_t tv_sec;
	long tv_nsec;
};

int __clock_nanosleep(clockid_t, int, const struct linux_timespec *, struct linux_timespec *);

int clock_nanosleep(clockid_t clk_id, int flags, const struct timespec *request, struct timespec *remain)
{
	clockid_t lid;
	const struct linux_timespec ltp = {request->tv_sec, request->tv_nsec};
	int ret;

	/* we could support these but not needed */
	if (flags != 0 || remain != NULL) {
		errno = EINVAL;
		return -1;
	}

	switch (clk_id) {
		case CLOCK_REALTIME:
			lid = LINUX_CLOCK_REALTIME;
			break;
		case CLOCK_MONOTONIC:
			lid = LINUX_CLOCK_MONOTONIC;
			break;
		default:
			errno = EINVAL;
			return -1;
	}

	ret = __clock_nanosleep(lid, 0, &ltp, NULL);

	if (ret != 0) {
		errno = EINVAL;
		return -1;
	}

	return 0;
}
