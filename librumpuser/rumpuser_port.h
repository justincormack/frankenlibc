#ifndef _LIB_LIBRUMPUSER_RUMPUSER_PORT_H_
#define _LIB_LIBRUMPUSER_RUMPUSER_PORT_H_

#ifndef MIN
#define MIN(a,b)        ((/*CONSTCOND*/(a)<(b))?(a):(b))
#endif
#ifndef MAX
#define MAX(a,b)        ((/*CONSTCOND*/(a)>(b))?(a):(b))
#endif

#ifndef __dead
#define __dead __attribute__((__noreturn__))
#endif

#ifndef _DIAGASSERT
#define _DIAGASSERT(_p_)
#endif

#ifndef __predict_true
#define __predict_true(a) a
#define __predict_false(a) a
#endif

#ifndef __printflike
#ifdef __GNUC__
#define __printflike(a,b) __attribute__((__format__ (__printf__,a,b)))
#else
#define __printflike(a,b)
#endif
#endif

#ifndef __noinline
#ifdef __GNUC__
#define __noinline __attribute__((__noinline__))
#else
#define __noinline
#endif
#endif

#ifndef __arraycount
#define __arraycount(_ar_) (sizeof(_ar_)/sizeof(_ar_[0]))
#endif

#ifndef __UNCONST
#define __UNCONST(_a_) ((void *)(unsigned long)(const void *)(_a_))
#endif

#ifndef __CONCAT
#define __CONCAT(x,y)	x ## y
#endif

#ifndef __STRING
#define __STRING(x)	#x
#endif

#ifndef __NetBSD_Prereq__
#define __NetBSD_Prereq__(a,b,c) 0
#endif

#endif /* _LIB_LIBRUMPUSER_RUMPUSER_PORT_H_ */
