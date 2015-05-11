#include <time.h>
#include <errno.h>

#include "syscall.h"

#include "linux.h"
#include "init.h"
#include "thread.h"

/* XXX tidy up */
extern int __platform_npoll;
extern struct pollfd __platform_pollfd[MAXFD];

int clock_nanosleep(clockid_t clk_id, int flags, const struct timespec *request, struct timespec *remain)
{
	clockid_t lid;
	struct linux_timespec ltp;
	int ret, i;
	struct thread *thread;

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

	if (__platform_npoll == 0) {
		ret = syscall(SYS_clock_nanosleep, lid, 0, &ltp, NULL);
		if (ret != 0) {
			errno = EINVAL;
			return -1;
		}
		return 0;
	}

	/* use poll instead as we might have network events */

	ret = syscall(SYS_ppoll, __platform_pollfd, __platform_npoll, &ltp, NULL);
	if (ret == -1) {
		errno = EINVAL;
		return -1;
	}

	if (ret == 0)
		return 0;

	for (i = 0; i < __platform_npoll; i++) {
		if (__platform_pollfd[i].revents) {
			thread = __franken_fd[__platform_pollfd[i].fd].wake;
			if (thread)
				wake(thread);
		}
	}

	return 0;
}
