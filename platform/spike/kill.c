#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int
kill(pid_t pid, int sig)
{

	_exit(1);
	return 0;
}
