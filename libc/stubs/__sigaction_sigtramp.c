#include <errno.h>

int __sigaction_sigtramp(int, const void *, void *, const void *, int);

int
__sigaction_sigtramp(int sig, const void *act, void *oact, const void *info, int f)
{

	errno = EINVAL;
	return -1;
}
