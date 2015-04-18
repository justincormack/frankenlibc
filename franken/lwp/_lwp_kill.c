#include <sys/types.h>
#include <lwp.h>

int __platform_kill(pid_t, int);

int
_lwp_kill(lwpid_t lwp, int sig)
{

	return __platform_kill(0, sig);
}
