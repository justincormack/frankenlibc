#include <unistd.h>

#define NCCS 20

typedef unsigned int	tcflag_t;
typedef unsigned char	cc_t;
typedef unsigned int	speed_t;

struct termios {
	tcflag_t	c_iflag;
	tcflag_t	c_oflag;
	tcflag_t	c_cflag;
	tcflag_t	c_lflag;
	cc_t		c_cc[NCCS];
	speed_t		c_ispeed;
	speed_t		c_ospeed;
};

#define IOCPARM_SHIFT	13
#define IOCPARM_MASK	((1 << IOCPARM_SHIFT) - 1)
#define IOC_OUT		0x40000000

#define _IOC(inout,group,num,len)       ((unsigned long) \
	((inout) | (((len) & IOCPARM_MASK) << 16) | ((group) << 8) | (num)))

#define _IOR(g,n,t)	_IOC(IOC_OUT, (g), (n), sizeof(t))

#define TIOCGETA _IOR('t', 19, struct termios)

int __ioctl(int, unsigned long, void *);

int
isatty(int fd)
{
	struct termios term;

	return __ioctl(fd, TIOCGETA, &term) != -1;
}
