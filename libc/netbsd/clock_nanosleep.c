#include <errno.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

#include "netbsd.h"

int __platform_sysctl(const int *, unsigned int, void *, size_t *, const void *, size_t);

int __clock_nanosleep(clockid_t, int, const struct timespec *, struct timespec *);
int __platform_nanosleep(const struct timespec *, struct timespec *);

int
clock_nanosleep(clockid_t clockid, int flags, const struct timespec *req, struct timespec *rem)
{
	static int __have_cns = -1;
	const int ctl[2] = {CTL_KERN, KERN_OSREV};
	int version;
	size_t lenp = sizeof(int);
	int ret;

	if (__have_cns == -1) {
		ret = __platform_sysctl(ctl, 2, &version, &lenp, NULL, 0);
		if (ret == -1)
			kill(0, SIGABRT);
		/* clock_nanosleep introduced in NetBSD 7 */
		if (version / 100000000 >= 7)
			__have_cns = 1;
		else
			__have_cns = 0;
	}
	if (__have_cns) {
		ret = __clock_nanosleep(clockid, flags, req, rem);
		if (ret != -1 || errno != ENOSYS) {
			return ret;
		}
		__have_cns = 0;
	}

	return __platform_nanosleep(req, rem);
}
