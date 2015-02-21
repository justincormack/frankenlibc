#include <signal.h>
#include <sys/types.h>

int __kill(pid_t, int);

int
raise(int signal)
{
	return __kill(0, signal);
}
