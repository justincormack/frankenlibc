#include <unistd.h>

#include "syscall.h"

void
_exit(int status)
{
	char die[] = "Terminating\n";

	write(1, die, sizeof(die));

	_syscall(SYS_exit, status, 0, 0);
	while (1) {};
}
