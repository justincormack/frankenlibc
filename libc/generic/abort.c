#include <signal.h>
#include <stdlib.h>

void
abort(void)
{

	raise(SIGABRT);
	exit(1);
}
