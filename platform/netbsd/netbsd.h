#define CTL_KERN 1
#define CTL_HW 6

#define KERN_OSREV 3
#define KERN_URND 61

#define HW_PAGESIZE 7

#define IOCPARM_MASK	0x1fff
#define IOCPARM_SHIFT	16
#define IOCGROUP_SHIFT	8

#define IOC_OUT		(unsigned long)0x40000000

#define _IOC(inout, group, num, len) \
    ((inout) | (((len) & IOCPARM_MASK) << IOCPARM_SHIFT) | \
    ((group) << IOCGROUP_SHIFT) | (num))

#define _IOR(g,n,t)	_IOC(IOC_OUT, (g), (n), sizeof(t))
