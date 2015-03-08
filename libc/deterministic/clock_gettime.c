#include <time.h>
#include <errno.h>

struct timespec __platform_now = {0 ,0};

int
clock_gettime(clockid_t clk_id, struct timespec *tp)
{

	if (! tp) {
		errno = EFAULT;
		return -1;
	}

	__platform_now.tv_nsec += 1000000;
	if (__platform_now.tv_nsec >= 1000000000) {
		__platform_now.tv_nsec -= 1000000000;
		__platform_now.tv_sec += 1;
	}

	tp->tv_sec = __platform_now.tv_sec;
	tp->tv_nsec = __platform_now.tv_nsec;

	return 0;
}
