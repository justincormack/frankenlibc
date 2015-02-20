#include <signal.h>
#include <stdlib.h>

void
abort(void)
{

	raise(SIGABRT);
	_exit(1);
}
