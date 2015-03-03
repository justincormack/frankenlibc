#define CTL_KERN 1
#define CTL_HW 6

#define KERN_ARND 37

#define HW_PAGESIZE 7

/* note on 64 bit platforms, FreeBSD timespec is the same as NetBSD,
   but this is not true on 32 bit platforms */

typedef long freebsd_time_t;

struct freebsd_timespec {
	freebsd_time_t tv_sec;
	long tv_nsec;
};

#define FREEBSD_CLOCK_REALTIME 0
#define FREEBSD_CLOCK_MONOTONIC 4 

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
