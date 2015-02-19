#ifndef _TIME_H_
#define _TIME_H_

#include <stddef.h>

typedef	int clockid_t;
typedef	long time_t;
struct timespec { time_t tv_sec; long tv_nsec; };

#define CLOCK_REALTIME 0
#if defined(__linux)
#define CLOCK_MONOTONIC 1
#else /* NetBSD */
#define CLOCK_MONOTONIC 3
#endif

int clock_gettime(clockid_t, struct timespec *);
int clock_nanosleep(clockid_t, int, const struct timespec *, struct timespec *);

#endif
