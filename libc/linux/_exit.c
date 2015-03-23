#include <unistd.h>

#include "syscall.h"

void
_exit(int status)
{

	for (;;) syscall(SYS_exit, status);
}
