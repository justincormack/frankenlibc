/*
 * Copyright (c) 2014 Justin Cormack.  All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef LIBRUMPUSER
#define LIBRUMPUSER
#endif
#include "rumpuser_port.h"

#include <sys/queue.h>

#include <stdint.h>
#include <string.h>
#include <time.h>
#include <ucontext.h>
#include <unistd.h>

#include <rump/rumpuser.h>

#define init_sched(h) __sched_init_sched(h)
#define schedule __sched_schedule
#define curlwp __sched_curlwp
#define set_curlwp(l) __sched_set_curlwp(l)
#define exit_thread __sched_exit_thread
#define create_thread(n, c, f, a, s, ss, j) __sched_create_thread(n, c, f, a, s, ss, j)
#define join_thread(t) __sched_join_thread(t)
#define clock_sleep(a, b, c) __sched_clock_sleep(a, b, c)
#define wake(t) __sched_wake(t)

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

struct thread;

void init_sched(const struct rumpuser_hyperup *);
void schedule(void);
void *curlwp(void);
void set_curlwp(void *lwp);
void exit_thread(void) __attribute__((noreturn));
struct thread *create_thread(const char *, void *,
	void (*)(void *), void *, void *, size_t, int);
void join_thread(struct thread *);
int clock_sleep(clockid_t, int64_t, long);
void wake(struct thread *);

struct rumpuser_mtx;
#define MTX_SPIN       0x01
#define MTX_KMUTEX     0x02
void mutex_init(struct rumpuser_mtx **, int);
void mutex_enter(struct rumpuser_mtx *);
void mutex_enter_nowrap(struct rumpuser_mtx *);
int  mutex_tryenter(struct rumpuser_mtx *);
void mutex_exit(struct rumpuser_mtx *);
void mutex_destroy(struct rumpuser_mtx *);
void mutex_owner(struct rumpuser_mtx *, void **);

struct rumpuser_rw;
#define RW_READER 0
#define RW_WRITER 1
void rw_init(struct rumpuser_rw **);
void rw_enter(int, struct rumpuser_rw *);
int  rw_tryenter(int, struct rumpuser_rw *);
int  rw_tryupgrade(struct rumpuser_rw *);
void rw_downgrade(struct rumpuser_rw *);
void rw_exit(struct rumpuser_rw *);
void rw_destroy(struct rumpuser_rw *);
void rw_held(int, struct rumpuser_rw *, int *);

struct rumpuser_cv;
void cv_init(struct rumpuser_cv **);
void cv_destroy(struct rumpuser_cv *);
void cv_wait(struct rumpuser_cv *, struct rumpuser_mtx *);
void cv_wait_nowrap(struct rumpuser_cv *, struct rumpuser_mtx *);
int  cv_timedwait(struct rumpuser_cv *, struct rumpuser_mtx *, int64_t, int64_t);
void cv_signal(struct rumpuser_cv *);
void cv_broadcast(struct rumpuser_cv *);
void cv_has_waiters(struct rumpuser_cv *, int *);
