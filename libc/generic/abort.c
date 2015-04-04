#include <signal.h>
#include <unistd.h>

void abort(void) __attribute__ ((weak));

void
abort()
{

	raise(SIGABRT);
	_exit(1);
}
