#include <stdlib.h>
#include <unistd.h>

void
_Exit(int status)
{

	_exit(status);
}
