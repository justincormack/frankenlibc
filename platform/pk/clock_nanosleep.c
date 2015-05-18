#include <time.h>
#include <errno.h>

extern struct timespec __platform_now;

int clock_nanosleep(clockid_t clk_id, int flags, const struct timespec *request, struct timespec *remain)
{

	if (! request) {
		errno = EFAULT;
		return -1;
	}

	__platform_now.tv_nsec += request->tv_nsec;
	if (__platform_now.tv_nsec >= 1000000000) {
		__platform_now.tv_nsec -= 1000000000;
		__platform_now.tv_sec += 1;
	}
	__platform_now.tv_sec += request->tv_sec;

	if (remain) {
		remain->tv_sec = 0;
		remain->tv_nsec = 0;
	}

	return 0;
}
