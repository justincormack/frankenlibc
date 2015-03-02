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

int __clock_gettime(clockid_t, struct freebsd_timespec *);

int
clock_gettime(clockid_t clk_id, struct timespec *tp)
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
	ret = __clock_gettime(fid, &ftp);

	if (ret != 0) {
		errno = EINVAL;
		return -1;
	}

	tp->tv_sec = ftp.tv_sec;
	tp->tv_nsec = ftp.tv_nsec;

	return 0;
}
