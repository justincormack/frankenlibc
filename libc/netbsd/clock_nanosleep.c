#include <errno.h>
#include <time.h>

int __clock_nanosleep(clockid_t, int, const struct timespec *, struct timespec *);
int __platform_nanosleep(const struct timespec *, struct timespec *);

static int __have_cns = 1;

int
clock_nanosleep(clockid_t clockid, int flags, const struct timespec *req, struct timespec *rem)
{
	int ret;

	if (__have_cns) {
		ret = __clock_nanosleep(clockid, flags, req, rem);
		if (ret != -1 || errno != ENOSYS) {
			return ret;
		}
		__have_cns = 0;
	}

	return __platform_nanosleep(req, rem); /* NetBSD 6 has no clock_nanosleep */
}
