#include <errno.h>
#include <time.h>

#include "freebsd.h"

int __clock_getres(clockid_t, struct freebsd_timespec *);

int
clock_getres(clockid_t clk_id, struct timespec *tp)
{
	clockid_t fid;
	struct freebsd_timespec ftp;
	int ret;

	switch (clk_id) {
		case CLOCK_REALTIME:
			fid = FREEBSD_CLOCK_REALTIME;
			break;
		case CLOCK_MONOTONIC:
			fid = FREEBSD_CLOCK_MONOTONIC;
			break;
		default:
			errno = EINVAL;
			return -1;
	}
	ret = __clock_getres(fid, &ftp);

	if (ret != 0) {
		errno = EINVAL;
		return -1;
	}

	tp->tv_sec = ftp.tv_sec;
	tp->tv_nsec = ftp.tv_nsec;

	return 0;
}
