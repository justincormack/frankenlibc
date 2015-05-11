#include <errno.h>
#include <time.h>

#include "freebsd.h"
#include "init.h"
#include "thread.h"

int __platform_nanosleep(const struct freebsd_timespec *, struct freebsd_timespec *);
int __platform_poll(struct pollfd[], nfds_t, int);

extern int __platform_npoll;
extern struct pollfd __platform_pollfd[MAXFD];

int
clock_nanosleep(clockid_t clockid, int flags, const struct timespec *req, struct timespec *rem)
{
	struct freebsd_timespec ftp = {req->tv_sec, req->tv_nsec};
	int i, ret, timeout;
	struct thread *thread;

	/* we could support these but not needed */
	if (flags != 0 || rem != NULL) {
		errno = EINVAL;
		return -1;
	}

	if (__platform_npoll == 0) {
		return __platform_nanosleep(&ftp, NULL);
	}

	/* use poll instead as we might have network events */

	timeout = req->tv_sec * 1000 + req->tv_nsec / 1000000;
	ret = __platform_poll(__platform_pollfd, __platform_npoll, timeout);

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
