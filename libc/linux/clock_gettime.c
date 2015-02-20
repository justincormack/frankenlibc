#include <time.h>
#include <errno.h>

#define LINUX_CLOCK_REALTIME 0
#define LINUX_CLOCK_MONOTONIC 1

/* note on 64 bit platforms, Linux timespec is the same as NetBSD,
   but this is not true on 32 bit platforms */

int __clock_gettime(clockid_t, struct timespec *);

int
clock_gettime(clockid_t clk_id, struct timespec *tp)
{
	clockid_t lid;

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
	/* TODO VDSO version */
	return __clock_gettime(lid, tp);
}
