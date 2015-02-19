#include <time.h>

int __clock_gettime(clockid_t, struct timespec *);

int
clock_gettime(clockid_t clk_id, struct timespec *tp)
{

	/* TODO VDSO version */
	return __clock_gettime(clk_id, tp);
}
