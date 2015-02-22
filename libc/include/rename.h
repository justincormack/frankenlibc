#ifndef _RENAME_H_
#define _RENAME_H_

/* namespace everything private into our namespace */

/* linux/random.h */
#define getrandom(b, s, f) __franken_getrandom(b, s, f)

/* signal.h */
#define kill(p, s) __franken_kill(p, s)
#define raise(s) __franken_raise(s)

/* stdio.h */
#define putchar(c) __franken_putchar(c)

/* stdlib.h */
#define abort __franken_abort
#define aligned_alloc(a, s) __franken_aligned_alloc(a, s)
#define getenv(n) __franken_getenv(n)

/* string.h */
#define memcpy(d, s, n) __franken_memcpy(d, s, n)
#define memset(s, c, n) __franken_memset(s, c, n)
#define strchr(s, c) __franken_strchr(s, c)
#define strcmp(s1, s2) __franken_strcmp(s1, s2)
#define strcpy(d, s) __franken_strcpy(d, s)
#define strdup(s) __franken_strdup(s)
#define strlen(s) __franken_strlen(s)
#define strncmp(s1, s2, n) __franken_strncmp(s1, s2, n)
#define strncpy(d, s, n) __franken_strncpy(d, s, n)

/* time.h */
#define clock_gettime(c, t) __franken_clock_gettime(c, t)
#define clock_nanosleep(c, f, req, rem) __franken_clock_nanosleep(c, f, req, rem)

/* ucontext.h */
#define getcontext(c) __franken_getcontext(c)
#define makecontext(c, f, i, a) __franken_makecontext(c, f, i, a)
#define swapcontext(c1, c2) __franken_swapcontext(c1, c2)

/* unistd.h */
#define getpagesize __franken_getpagesize
#define isatty(f) __franken_isatty(f)
#define write(f, b, c) __franken_write(f, b, c)

#endif
