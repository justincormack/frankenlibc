#include <unistd.h>

#include "syscall.h"

typedef unsigned int tcflag_t;
typedef unsigned char cc_t;

struct termios {
	tcflag_t c_iflag;
	tcflag_t c_oflag;
	tcflag_t c_cflag;
	tcflag_t c_lflag;
	cc_t c_line;
	cc_t c_cc[19];
};

int __ioctl(int, unsigned long, void *);

int
isatty(int fd)
{
	struct termios term;

	return __ioctl(fd, TCGETS, &term) != -1;
}
