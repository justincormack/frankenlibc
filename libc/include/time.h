#ifndef _TIME_H_
#define _TIME_H_

#include <stddef.h>
#include <stdint.h>

#include <rename.h>

typedef	int clockid_t;
typedef	int64_t time_t;
struct timespec { time_t tv_sec; long tv_nsec; };

#define CLOCK_REALTIME 0
#define CLOCK_MONOTONIC 3

int clock_gettime(clockid_t, struct timespec *);
int clock_nanosleep(clockid_t, int, const struct timespec *, struct timespec *);

#endif
