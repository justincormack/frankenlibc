#include <unistd.h>

#include "syscall.h"

#include "linux.h"

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

int
isatty(int fd)
{
	struct termios term;

	return syscall(SYS_ioctl, fd, TCGETS, &term) != -1;
}
