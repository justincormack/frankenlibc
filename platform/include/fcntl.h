#ifndef _FCNTL_H_
#define _FCNTL_H_

#define O_RDONLY        0x00000000
#define O_WRONLY        0x00000001
#define O_RDWR          0x00000002
#define O_ACCMODE       0x00000003

#define F_GETFL 	3

#define fcntl(f, a, b) __platform_fcntl(f, a, b)

int fcntl(int, int, ...);

#endif
