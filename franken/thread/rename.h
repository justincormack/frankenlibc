#define init_sched(h) __sched_init_sched(h)
#define schedule __sched_schedule
#define curlwp __sched_curlwp
#define set_curlwp(l) __sched_set_curlwp(l)
#define exit_thread __sched_exit_thread
#define create_thread(n, c, f, a, s, ss, j) __sched_create_thread(n, c, f, a, s, ss, j)
#define join_thread(t) __sched_join_thread(t)

#define mutex_init(m, i) __sched_mutex_init(m, i)
#define mutex_enter(m) __sched_mutex_enter(m)
#define mutex_enter_nowrap(m) __sched_mutex_enter_nowrap(m)
#define mutex_tryenter(m) __sched_mutex_tryenter(m)
#define mutex_exit(m) __sched_mutex_exit(m)
#define mutex_destroy(m) __sched_mutex_destroy(m)
#define mutex_owner(m, l) __sched_mutex_owner(m, l)

#define rw_init(r) __sched_rw_init(r)
#define rw_enter(i, r) __sched_rw_enter(i, r)
#define rw_tryenter(i, r) __sched_rw_tryenter(i, r)
#define rw_tryupgrade(r) __sched_rw_tryupgrade(r)
#define rw_downgrade(r) __sched_rw_downgrade(r)
#define rw_exit(w) __sched_rw_exit(w)
#define rw_destroy(r) __sched_rw_destroy(r)
#define rw_held(i, r, j) __sched_rw_held(i, r, j)

#define cv_init(c) __sched_cv_init(c)
#define cv_destroy(c) __sched_cv_destroy(c)
#define cv_wait(c, m) __sched_cv_wait(c, m)
#define cv_wait_nowrap(c, m) __sched_cv_wait_nowrap(c, m)
#define cv_timedwait(c, m, a, b) __sched_cv_timedwait(c, m, a, b)
#define cv_signal(c) __sched_cv_signal(c)
#define cv_broadcast(c) __sched_cv_broadcast(c)
#define cv_has_waiters(c, i) __sched_cv_has_waiters(c, i)
