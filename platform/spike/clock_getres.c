#include <time.h>
#include <errno.h>

int
clock_getres(clockid_t clk_id, struct timespec *tp)
{

	if (! tp) {
		errno = EFAULT;
		return -1;
	}

	tp->tv_sec = 0;
	tp->tv_nsec = 1000000;

	return 0;
}
