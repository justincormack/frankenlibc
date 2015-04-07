#include <signal.h>
#include <unistd.h>

void abort(void) __attribute__ ((weak));

void
abort()
{

	kill(0, SIGABRT);
	_exit(1);
}
