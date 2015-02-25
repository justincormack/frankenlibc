#include <sys/types.h>

/* cannot include <signal.h> due to renaming */

/* always abort as only provided signal */

#define SIGABRT 6

int kill(pid_t, int);
int __franken_kill(pid_t, int);

int
kill(pid_t pid, int sig)
{

	__franken_kill(0, SIGABRT);

	return 0;
}
