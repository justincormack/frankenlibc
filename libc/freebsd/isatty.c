#include <unistd.h>

#include "freebsd.h"

int __ioctl(int, unsigned long, void *);

int
isatty(int fd)
{
	struct termios term;

	return __ioctl(fd, TIOCGETA, &term) != -1;
}
