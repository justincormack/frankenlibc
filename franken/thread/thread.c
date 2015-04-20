/*
 * Copyright (c) 2007-2013 Antti Kantee.  All Rights Reserved.
 * Copyright (c) 2014-2015 Justin Cormack.  All Rights Reserved.
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

/* Based partly on code from Xen Minios with the following license */

/* 
 ****************************************************************************
 * (C) 2005 - Grzegorz Milos - Intel Research Cambridge
 ****************************************************************************
 *
 *        File: sched.c
 *      Author: Grzegorz Milos
 *     Changes: Robert Kaiser
 *              
 *        Date: Aug 2005
 * 
 * Environment: Xen Minimal OS
 * Description: simple scheduler for Mini-Os
 *
 * The scheduler is non-preemptive (cooperative), and schedules according 
 * to Round Robin algorithm.
 *
 ****************************************************************************
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
 * DEALINGS IN THE SOFTWARE.
 */

#include <sys/mman.h>
#include <sys/time.h>

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "thread.h"

struct rumpuser_hyperup rumpuser__hyp;

static inline void
rumpkern_unsched(int *nlocks, void *interlock)
{

        rumpuser__hyp.hyp_backend_unschedule(0, nlocks, interlock);
}

static inline void
rumpkern_sched(int nlocks, void *interlock)
{

        rumpuser__hyp.hyp_backend_schedule(nlocks, interlock);
}

struct thread {
	char *name;
	void *lwp;
	void *cookie;
	int64_t wakeup_time;
	TAILQ_ENTRY(thread) thread_list;
	ucontext_t ctx;
	int flags;
	int threrrno;
};

#define RUNNABLE_FLAG   0x00000001
#define THREAD_MUSTJOIN 0x00000002
#define THREAD_JOINED   0x00000004
#define THREAD_EXTSTACK 0x00000008
#define THREAD_TIMEDOUT 0x00000010

#ifndef STACKSIZE
#define STACKSIZE 65536
#endif

static void switch_threads(struct thread *, struct thread *);
static int64_t now(void);

TAILQ_HEAD(thread_list, thread);

static struct thread_list exited_threads = TAILQ_HEAD_INITIALIZER(exited_threads);
static struct thread_list thread_list = TAILQ_HEAD_INITIALIZER(thread_list);
static struct thread *current_thread = NULL;

static void (*scheduler_hook)(void *, void *);

TAILQ_HEAD(waithead, waiter);
struct waiter {
	struct thread *who;
	TAILQ_ENTRY(waiter) entries;
	int onlist;
};

static void wake(struct thread *);
static void block(struct thread *);
static int is_runnable(struct thread *);
static void set_runnable(struct thread *);
static void clear_runnable(struct thread *);
static void set_sched_hook(void (*)(void *, void *));
static int wait(struct waithead *, int64_t);
static void wakeup_one(struct waithead *);
static void wakeup_all(struct waithead *);
static struct thread *get_current(void);

static void printk(const char *);

static void
printk(const char *msg)
{
	int ret __attribute__((unused));

	ret = write(2, msg, strlen(msg));
}

static struct thread *
get_current(void)
{

	return current_thread;
}

void *
curlwp()
{

	return current_thread->lwp;
}

void
set_curlwp(void *lwp)
{

	current_thread->lwp = lwp;
}

static int64_t
now(void)
{
	struct timespec ts;
	int rv;

	rv = clock_gettime(CLOCK_MONOTONIC, &ts);
	assert(rv == 0);
	return (ts.tv_sec * 1000LL) + (ts.tv_nsec / 1000000LL);
}

void
schedule(void)
{
	struct thread *prev, *next, *thread, *tmp;
	int64_t tm, wakeup;
	struct timespec sl;

	prev = get_current();

	do {
		tm = now();	
		wakeup = tm + 1000; /* wake up in 1s max */
		next = NULL;
		TAILQ_FOREACH_SAFE(thread, &thread_list, thread_list, tmp) {
			if (!is_runnable(thread) && thread->wakeup_time >= 0) {
				if (thread->wakeup_time <= tm) {
					thread->flags |= THREAD_TIMEDOUT;
					wake(thread);
				} else if (thread->wakeup_time < wakeup)
					wakeup = thread->wakeup_time;
			}
			if (is_runnable(thread)) {
				next = thread;
				/* Put this thread on the end of the list */
				TAILQ_REMOVE(&thread_list, thread, thread_list);
				TAILQ_INSERT_TAIL(&thread_list, thread, thread_list);
				break;
			}
		}
		if (next)
			break;
		sl.tv_sec = (wakeup - tm) / 1000;
		sl.tv_nsec = ((wakeup - tm) - 1000 * sl.tv_sec) * 1000000;
		clock_nanosleep(CLOCK_MONOTONIC, 0, &sl, NULL);
	} while (1);

	if (prev != next)
		switch_threads(prev, next);

	TAILQ_FOREACH_SAFE(thread, &exited_threads, thread_list, tmp) {
		if (thread != prev) {
			TAILQ_REMOVE(&exited_threads, thread, thread_list);
			if ((thread->flags & THREAD_EXTSTACK) == 0)
				munmap(thread->ctx.uc_stack.ss_sp, STACKSIZE);
			free(thread->name);
			free(thread);
		}
	}
}

static void
create_ctx(ucontext_t *ctx, void *stack, size_t stack_size,
	void (*f)(void *), void *data)
{

	getcontext(ctx);
	ctx->uc_stack.ss_sp = stack;
	ctx->uc_stack.ss_size = stack_size;
	ctx->uc_stack.ss_flags = 0;
	ctx->uc_link = NULL; /* TODO may link to main thread */
	makecontext(ctx, (void (*)(void))f, 1, data);
}

struct thread *
create_thread(const char *name, void *cookie, void (*f)(void *), void *data,
	void *stack, size_t stack_size, int joinable)
{
	struct thread *thread = calloc(1, sizeof(struct thread));

	if (!thread) {
		return NULL;
	}

	if (joinable)
		thread->flags |= THREAD_MUSTJOIN;

	if (!stack) {
		assert(stack_size == 0);
		stack = mmap(NULL, STACKSIZE, PROT_READ | PROT_WRITE,
		    MAP_SHARED | MAP_ANON | MAP_STACK, -1, 0);
		if (stack == MAP_FAILED) {
			free(thread);
			return NULL;
		}
		stack_size = STACKSIZE;
	} else {
		thread->flags = THREAD_EXTSTACK;
	}
	create_ctx(&thread->ctx, stack, stack_size, f, data);
	
	thread->name = strdup(name);
	thread->cookie = cookie;

	/* Not runnable, not exited, not sleeping */
	thread->wakeup_time = -1;
	thread->lwp = NULL;
	set_runnable(thread);
	TAILQ_INSERT_TAIL(&thread_list, thread, thread_list);

	return thread;
}

static void
switch_threads(struct thread *prev, struct thread *next)
{
	int ret;

	current_thread = next;
	if (scheduler_hook)
		scheduler_hook(prev->cookie, next->cookie);
	ret = swapcontext(&prev->ctx, &next->ctx);
	if (ret < 0) {
		printk("swapcontext failed\n");
		abort();
	}
}

struct join_waiter {
    struct thread *jw_thread;
    struct thread *jw_wanted;
    TAILQ_ENTRY(join_waiter) jw_entries;
};
static TAILQ_HEAD(, join_waiter) joinwq = TAILQ_HEAD_INITIALIZER(joinwq);

void
exit_thread(void)
{
	struct thread *thread = get_current();
	struct join_waiter *jw_iter;

	/* if joinable, gate until we are allowed to exit */
	while (thread->flags & THREAD_MUSTJOIN) {
		thread->flags |= THREAD_JOINED;

		/* see if the joiner is already there */
		TAILQ_FOREACH(jw_iter, &joinwq, jw_entries) {
			if (jw_iter->jw_wanted == thread) {
				wake(jw_iter->jw_thread);
				break;
			}
		}
		block(thread);
		schedule();
	}

	/* Remove from the thread list */
	TAILQ_REMOVE(&thread_list, thread, thread_list);
	clear_runnable(thread);
	/* Put onto exited list */
	TAILQ_INSERT_HEAD(&exited_threads, thread, thread_list);

	/* Schedule will free the resources */
	while (1) {
		schedule();
		printk("schedule() returned!  Trying again\n");
	}
}

void
join_thread(struct thread *joinable)
{
	struct join_waiter jw;
	struct thread *thread = get_current();

	assert(joinable->flags & THREAD_MUSTJOIN);

	/* wait for exiting thread to hit thread_exit() */
	while (! (joinable->flags & THREAD_JOINED)) {

		jw.jw_thread = thread;
		jw.jw_wanted = joinable;
		TAILQ_INSERT_TAIL(&joinwq, &jw, jw_entries);
		block(thread);
		schedule();
		TAILQ_REMOVE(&joinwq, &jw, jw_entries);
	}

	/* signal exiting thread that we have seen it and it may now exit */
	assert(joinable->flags & THREAD_JOINED);
	joinable->flags &= ~THREAD_MUSTJOIN;

	wake(joinable);
}

static void msleep(int64_t millisecs)
{
	struct thread *thread = get_current();

	thread->wakeup_time = now() + millisecs;
	clear_runnable(thread);
	schedule();
}

static void abssleep(int64_t millisecs)
{
	struct thread *thread = get_current();

	thread->wakeup_time = millisecs;
	clear_runnable(thread);
	schedule();
}

/* XXX unused */
/* like abssleep, except against realtime clock instead of monotonic clock */
static int abssleep_real(int64_t millisecs)
{
	struct thread *thread = get_current();
	struct timespec ts;
	int64_t real_now;
	int rv;

	clock_gettime(CLOCK_REALTIME, &ts);
	real_now = 1000*ts.tv_sec + ts.tv_nsec/(1000*1000);
	thread->wakeup_time = now() + (millisecs - real_now);

	clear_runnable(thread);
	schedule();

	rv = !!(thread->flags & THREAD_TIMEDOUT);
	thread->flags &= ~THREAD_TIMEDOUT;
	return rv;
}

/* XXX convert to clock_nanosleep */
int
clock_sleep(clockid_t clk, int64_t sec, long nsec)
{
	int64_t msec;
	int nlocks;

	rumpkern_unsched(&nlocks, NULL);
	switch (clk) {
	case CLOCK_REALTIME:
		msec = sec * 1000 + nsec / (1000*1000UL);
		msleep(msec);
		break;
	case CLOCK_MONOTONIC:
		msec = sec * 1000 + nsec / (1000*1000UL);
		abssleep(msec);
		break;
	}
	rumpkern_sched(nlocks, NULL);

	return 0;
}

static void
wake(struct thread *thread)
{

	thread->wakeup_time = -1;
	set_runnable(thread);
}

static void
block(struct thread *thread)
{

	thread->wakeup_time = -1;
	clear_runnable(thread);
}

static int
is_runnable(struct thread *thread)
{

	return thread->flags & RUNNABLE_FLAG;
}

static void
set_runnable(struct thread *thread)
{

	thread->flags |= RUNNABLE_FLAG;
}

static void
clear_runnable(struct thread *thread)
{

	thread->flags &= ~RUNNABLE_FLAG;
}

void
init_sched(const struct rumpuser_hyperup *hyp)
{
	struct thread *thread = calloc(1, sizeof(struct thread));

	if (! thread)
		abort();

	rumpuser__hyp = *hyp;

	thread->name = strdup("init");
	thread->flags = 0;
	thread->wakeup_time = -1;
	thread->lwp = NULL;
	set_runnable(thread);
	TAILQ_INSERT_TAIL(&thread_list, thread, thread_list);
	current_thread = thread;
}

static void
set_sched_hook(void (*f)(void *, void *))
{

	scheduler_hook = f;
}

/* XXX unused, see if thread code needs it */
static struct thread *
init_mainthread(void *cookie)
{

	current_thread->cookie = cookie;
	return current_thread;
}

#define WAIT_NOTIMEOUT -1

static int
wait(struct waithead *wh, time_t msec)
{
	struct waiter w;
	time_t wakeup;

	w.who = get_current();
	TAILQ_INSERT_TAIL(wh, &w, entries);
	w.onlist = 1;
	block(w.who);
	if (msec == WAIT_NOTIMEOUT)
		w.who->wakeup_time = -1;
	else
		w.who->wakeup_time = now() + msec;
	clear_runnable(w.who);
	schedule();

	/* woken up by timeout? */
	if (w.onlist)
		TAILQ_REMOVE(wh, &w, entries);

	return w.onlist ? ETIMEDOUT : 0;
}

static void
wakeup_one(struct waithead *wh)
{
	struct waiter *w;

	if ((w = TAILQ_FIRST(wh)) != NULL) {
		TAILQ_REMOVE(wh, w, entries);
		w->onlist = 0;
		wake(w->who);
	}
}

static void
wakeup_all(struct waithead *wh)
{
	struct waiter *w;

	while ((w = TAILQ_FIRST(wh)) != NULL) {
		TAILQ_REMOVE(wh, w, entries);
		w->onlist = 0;
		wake(w->who);
	}
}

/* mtx */

struct rumpuser_mtx {
	struct waithead waiters;
	int v;
	int flags;
	struct lwp *o;
};

void
mutex_init(struct rumpuser_mtx **mtxp, int flags)
{
	struct rumpuser_mtx *mtx;

	mtx = calloc(1, sizeof(*mtx));
	if (! mtx) abort();
	mtx->flags = flags;
	TAILQ_INIT(&mtx->waiters);
	*mtxp = mtx;
}

void
mutex_enter(struct rumpuser_mtx *mtx)
{
	int nlocks;

	if (mutex_tryenter(mtx) != 0) {
		rumpkern_unsched(&nlocks, NULL);
		while (mutex_tryenter(mtx) != 0)
			wait(&mtx->waiters, WAIT_NOTIMEOUT);
		rumpkern_sched(nlocks, NULL);
	}
}

void
mutex_enter_nowrap(struct rumpuser_mtx *mtx)
{
	int rv;

	rv = mutex_tryenter(mtx);
	/* one VCPU supported, no preemption => must succeed */
	if (rv != 0) {
		abort();
	}
}

int
mutex_tryenter(struct rumpuser_mtx *mtx)
{
	struct lwp *l = get_current()->lwp;

	if (mtx->v && mtx->o != l)
		return EBUSY;

	mtx->v++;
	mtx->o = l;

	return 0;
}

void
mutex_exit(struct rumpuser_mtx *mtx)
{

	assert(mtx->v > 0);
	if (--mtx->v == 0) {
		mtx->o = NULL;
		wakeup_one(&mtx->waiters);
	}
}

void
mutex_destroy(struct rumpuser_mtx *mtx)
{

	assert(TAILQ_EMPTY(&mtx->waiters) && mtx->o == NULL);
	free(mtx);
}

void
mutex_owner(struct rumpuser_mtx *mtx, void **lp)
{

	*lp = mtx->o;
}

struct rumpuser_rw {
	struct waithead rwait;
	struct waithead wwait;
	int v;
	struct lwp *o;
};

void
rw_init(struct rumpuser_rw **rwp)
{
	struct rumpuser_rw *rw;

	rw = calloc(1, sizeof(*rw));
	if (!rw) abort();
	TAILQ_INIT(&rw->rwait);
	TAILQ_INIT(&rw->wwait);

	*rwp = rw;
}

void
rw_enter(int lk, struct rumpuser_rw *rw)
{
	struct waithead *w = NULL;
	int nlocks;

	switch (lk) {
	case RW_WRITER:
		w = &rw->wwait;
		break;
	case RW_READER:
		w = &rw->rwait;
		break;
	}

	if (rw_tryenter(lk, rw) != 0) {
		rumpkern_unsched(&nlocks, NULL);
		while (rw_tryenter(lk, rw) != 0)
			wait(w, WAIT_NOTIMEOUT);
		rumpkern_sched(nlocks, NULL);
	}
}

int
rw_tryenter(int lk, struct rumpuser_rw *rw)
{
	int rv;

	switch (lk) {
	case RW_WRITER:
		if (rw->o == NULL) {
			rw->o = curlwp();
			rv = 0;
		} else {
			rv = EBUSY;
		}
		break;
	case RW_READER:
		if (rw->o == NULL && TAILQ_EMPTY(&rw->wwait)) {
			rw->v++;
			rv = 0;
		} else {
			rv = EBUSY;
		}
		break;
	default:
		rv = EINVAL;
	}

	return rv;
}

void
rw_exit(struct rumpuser_rw *rw)
{

	if (rw->o) {
		rw->o = NULL;
	} else {
		rw->v--;
	}

	/* standard procedure, don't let readers starve out writers */
	if (!TAILQ_EMPTY(&rw->wwait)) {
		if (rw->o == NULL)
			wakeup_one(&rw->wwait);
	} else if (!TAILQ_EMPTY(&rw->rwait) && rw->o == NULL) {
		wakeup_all(&rw->rwait);
	}
}

void
rw_destroy(struct rumpuser_rw *rw)
{

	free(rw);
}

void
rw_held(int lk, struct rumpuser_rw *rw, int *rvp)
{

	switch (lk) {
	case RW_WRITER:
		*rvp = rw->o == curlwp();
		break;
	case RW_READER:
		*rvp = rw->v > 0;
		break;
	}
}

void
rw_downgrade(struct rumpuser_rw *rw)
{

	assert(rw->o == curlwp());
	rw->v = -1;
}

int
rw_tryupgrade(struct rumpuser_rw *rw)
{

	if (rw->v == -1) {
		rw->v = 1;
		rw->o = curlwp();
		return 0;
	}

	return EBUSY;
}

struct rumpuser_cv {
	struct waithead waiters;
	int nwaiters;
};

void
cv_init(struct rumpuser_cv **cvp)
{
	struct rumpuser_cv *cv;

	cv = calloc(1, sizeof(*cv));
	if (!cv) abort();
	TAILQ_INIT(&cv->waiters);
	*cvp = cv;
}

void
cv_destroy(struct rumpuser_cv *cv)
{

	assert(cv->nwaiters == 0);
	free(cv);
}

static void
cv_unsched(struct rumpuser_mtx *mtx, int *nlocks)
{

	rumpkern_unsched(nlocks, mtx);
	mutex_exit(mtx);
}

static void
cv_resched(struct rumpuser_mtx *mtx, int nlocks)
{

	/* see rumpuser(3) */
	if ((mtx->flags & (MTX_KMUTEX | MTX_SPIN)) ==
	    (MTX_KMUTEX | MTX_SPIN)) {
		rumpkern_sched(nlocks, mtx);
		mutex_enter_nowrap(mtx);
	} else {
		mutex_enter_nowrap(mtx);
		rumpkern_sched(nlocks, mtx);
	}
}

void
cv_wait(struct rumpuser_cv *cv, struct rumpuser_mtx *mtx)
{
	int nlocks;

	cv->nwaiters++;
	cv_unsched(mtx, &nlocks);
	wait(&cv->waiters, WAIT_NOTIMEOUT);
	cv_resched(mtx, nlocks);
	cv->nwaiters--;
}

void
cv_wait_nowrap(struct rumpuser_cv *cv, struct rumpuser_mtx *mtx)
{

	cv->nwaiters++;
	mutex_exit(mtx);
	wait(&cv->waiters, WAIT_NOTIMEOUT);
	mutex_enter_nowrap(mtx);
	cv->nwaiters--;
}

int
cv_timedwait(struct rumpuser_cv *cv, struct rumpuser_mtx *mtx, int64_t sec, int64_t nsec)
{
	int nlocks;
	int rv;

	cv->nwaiters++;
	cv_unsched(mtx, &nlocks);
	rv = wait(&cv->waiters, sec * 1000 + nsec / (1000*1000));
	cv_resched(mtx, nlocks);
	cv->nwaiters--;

	return rv;
}

void
cv_signal(struct rumpuser_cv *cv)
{

	wakeup_one(&cv->waiters);
}

void
cv_broadcast(struct rumpuser_cv *cv)
{

	wakeup_all(&cv->waiters);
}

void
cv_has_waiters(struct rumpuser_cv *cv, int *rvp)
{

	*rvp = cv->nwaiters != 0;
}
