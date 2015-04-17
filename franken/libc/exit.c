#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define COUNT 34

static struct {
	int n;
	void (*f[COUNT])(void);
} handlers;

int
atexit(void (*function)(void))
{

	if (handlers.n == COUNT) {
		errno = ENOMEM;
		return -1;
	}

	handlers.f[handlers.n++] = function;

	return 0;
}

void
exit(int status)
{

	while (handlers.n > 0)
		handlers.f[--handlers.n]();
		
	_exit(status);
}
