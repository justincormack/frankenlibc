#ifndef _RENAME_H_
#define _RENAME_H_

/* namespace everything private into our namespace */

/* linux/random.h */
#define getrandom(b, s, f) __platform_getrandom(b, s, f)

/* signal.h */
#define kill(p, s) __platform_kill(p, s)

/* stdio.h */
#define putchar(c) __franken_putchar(c)

/* time.h */
#define clock_getres(c, t) __platform_clock_getres(c, t)
#define clock_gettime(c, t) __platform_clock_gettime(c, t)
#define clock_nanosleep(c, f, req, rem) __platform_clock_nanosleep(c, f, req, rem)

/* ucontext.h */
#define getcontext(c) __franken_getcontext(c)
#define makecontext(c, f, i, a) __franken_makecontext(c, f, i, a)
#define swapcontext(c1, c2) __franken_swapcontext(c1, c2)

/* unistd.h */
#define fsync(f) __platform_fsync(f)
#define getpagesize __platform_getpagesize
#define isatty(f) __platform_isatty(f)
#define pread(a, b, c, d) __platform_pread(a, b, c, d)
#define pwrite(a, b, c, d) __platform_pwrite(a, b, c, d)
#define read(f, b, c) __platform_read(f, b, c)
#define write(f, b, c) __platform_write(f, b, c)

/* sys.mman.h */
#define mmap(a, b, c, d, e, f) __platform_mmap(a, b, c, d, e, f)

/* sys/stat.h */
#define fstat(f, s) __platform_fstat(f, s)

#endif
