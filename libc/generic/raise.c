#include <signal.h>
#include <sys/types.h>

int
raise(int signal)
{
	return kill(0, signal);
}
