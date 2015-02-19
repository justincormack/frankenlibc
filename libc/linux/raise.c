#include <signal.h>
#include <sys/types.h>

int kill(pid_t, int);

int
raise(int signal)
{
	return kill(0, signal);
}
