#include <time.h>
#include <errno.h>

#include "syscall.h"

#include "linux.h"

int clock_nanosleep(clockid_t clk_id, int flags, const struct timespec *request, struct timespec *remain)
{
	clockid_t lid;
	struct linux_timespec ltp;
	int ret;

	ltp.tv_sec = request->tv_sec;
	ltp.tv_nsec = request->tv_nsec;

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

	ret = syscall(SYS_clock_nanosleep, lid, 0, &ltp, NULL);

	if (ret != 0) {
		errno = EINVAL;
		return -1;
	}

	return 0;
}
