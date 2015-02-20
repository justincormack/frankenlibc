#ifndef _ERRNO_H_
#define _ERRNO_H_

extern int errno;

int *__errno(void);

#define ENOENT		2
#define EBADF		9
#define	ENOMEM		12
#define EBUSY		16
#define EINVAL		22
#define ERANGE		34
#if defined(__linux__)
#define ETIMEDOUT	110
#define ENOSYS		38
#else /* NetBSD */
#define ETIMEDOUT	60
#define ENOSYS		78
#endif

#endif
