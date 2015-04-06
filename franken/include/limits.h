#ifndef _LIMITS_H_
#define _LIMITS_H_

#if __SIZEOF_LONG__ == 4
#define ULONG_MAX 0xffffffff
#else
#define ULONG_MAX 0xffffffffffffffff
#endif

#endif
