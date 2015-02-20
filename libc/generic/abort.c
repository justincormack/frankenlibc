#include <signal.h>
#include <unistd.h>

void
abort(void)
{

	raise(SIGABRT);
	_exit(1);
}
