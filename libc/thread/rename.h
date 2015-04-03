#define init_sched(h) __sched_init_sched(h)
#define schedule __sched_schedule
#define curlwp __sched_curlwp
#define set_curlwp(l) __sched_set_curlwp(l)
#define exit_thread __sched_exit_thread
#define create_thread(n, c, f, a, s, ss, j) __sched_create_thread(n, c, f, a, s, ss, j)
#define join_thread(t) __sched_join_thread(t)
