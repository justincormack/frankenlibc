#define init_sched(h) __sched_init_sched(h)
#define schedule __sched_schedule
#define get_current __sched_get_current
#define curlwp __sched_curlwp
#define set_curlwp(l) __sched_set_curlwp(l)
#define wake(t) __sched_wake(t)
#define block(t) __sched_block(t)
#define init_mainthread __sched_init_mainthread
#define exit_thread __sched_exit_thread
#define set_sched_hook(f) sched_set_sched_hook(f)
#define abssleep_real(t) __sched_abssleep_real(t)
#define create_thread(n, c, f, a, s, ss, j) __sched_create_thread(n, c, f, a, s, ss, j)
#define is_runnable(t) __sched_is_runnable(t)
#define set_runnable(t) __sched_set_runnable(t)
#define clear_runnable(t) __sched_clear_runnable(t)
#define join_thread(t) __sched_join_thread(t)
#define msleep(t) __sched_msleep(t)
#define abssleep(t) __sched_abssleep(t)
#define wait(w, t) __sched_wait(w, t)
#define wakeup_one(w) __sched_wakeup_one(w)
#define wakeup_all(w) __sched_wakeup_all(w)
