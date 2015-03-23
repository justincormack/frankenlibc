#include <time.h>
#include <errno.h>

#include "syscall.h"

#include "linux.h"

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
	ret = syscall(SYS_clock_gettime, lid, &ltp);

	if (ret != 0) {
		errno = EINVAL;
		return -1;
	}

	tp->tv_sec = ltp.tv_sec;
	tp->tv_nsec = ltp.tv_nsec;

	return 0;
}
