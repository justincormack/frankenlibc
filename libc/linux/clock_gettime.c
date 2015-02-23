#include <time.h>
#include <errno.h>

/* XXX do a VDSO version for performance */

#define LINUX_CLOCK_REALTIME 0
#define LINUX_CLOCK_MONOTONIC 1

/* note on 64 bit platforms, Linux timespec is the same as NetBSD,
   but this is not true on 32 bit platforms */

typedef long linux_time_t;

struct linux_timespec {
	linux_time_t tv_sec;
	long tv_nsec;
};

int __clock_gettime(clockid_t, struct linux_timespec *);

int
clock_gettime(clockid_t clk_id, struct timespec *tp)
{
	clockid_t lid;
	struct linux_timespec ltp;
	int ret;

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
	ret = __clock_gettime(lid, &ltp);

	if (ret != 0) {
		errno = EINVAL;
		return -1;
	}

	tp->tv_sec = ltp.tv_sec;
	tp->tv_nsec = ltp.tv_nsec;

	return 0;
}
