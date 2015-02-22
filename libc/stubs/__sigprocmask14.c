#include <errno.h>

int __sigprocmask14(int, const void *, void *);

int
__sigprocmask14(int how, const void *set, void *oset)
{

	errno = EINVAL;
	return -1;
}
