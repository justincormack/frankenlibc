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
	int		c_ispeed;
	int		c_ospeed;
};

#define IOCPARM_MASK	0x1fff
#define IOCPARM_SHIFT	16
#define IOCGROUP_SHIFT	8

#define IOC_OUT		(unsigned long)0x40000000

#define _IOC(inout, group, num, len) \
    ((inout) | (((len) & IOCPARM_MASK) << IOCPARM_SHIFT) | \
    ((group) << IOCGROUP_SHIFT) | (num))

#define _IOR(g,n,t)	_IOC(IOC_OUT, (g), (n), sizeof(t))

#define TIOCGETA _IOR('t', 19, struct termios)

int __ioctl(int, unsigned long, void *);

int
isatty(int fd)
{
	struct termios term;

	return __ioctl(fd, TIOCGETA, &term) != -1;
}
