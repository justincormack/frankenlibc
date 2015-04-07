#include <signal.h>
#include <unistd.h>

void
abort()
{

	kill(0, SIGABRT);
	_exit(1);
}
