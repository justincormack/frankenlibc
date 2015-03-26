#include <sys/types.h>

/* cannot include <signal.h> due to renaming */

/* always abort as only provided signal */

#define SIGABRT 6

int kill(pid_t, int);
int __platform_kill(pid_t, int);

int
kill(pid_t pid, int sig)
{

	__platform_kill(0, SIGABRT);

	return 0;
}
