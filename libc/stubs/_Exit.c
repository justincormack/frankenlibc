#include <unistd.h>

void _Exit(int);

void
_Exit(int status)
{

	_exit(status);
}
