/*	$NetBSD: rumpfiber.c,v 1.9 2014/12/29 21:50:09 justin Exp $	*/

/*
 * Copyright (c) 2007-2013 Antti Kantee.  All Rights Reserved.
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

#include "rumpuser_port.h"

#include <sys/mman.h>
#include <sys/time.h>

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <rump/rumpuser.h>

#include "rumpuser_int.h"
#include "thread.h"

static void printk(const char *s);

static void
printk(const char *msg)
{
	int ret __attribute__((unused));

	ret = write(2, msg, strlen(msg));
}

int
rumpuser_init(int version, const struct rumpuser_hyperup *hyp)
{

	if (version != RUMPUSER_VERSION) {
		printk("rumpuser version mismatch\n");
		abort();
	}

        rumpuser__hyp = *hyp;

	init_sched(hyp);

        return 0;
}

int
rumpuser_clock_gettime(int enum_rumpclock, int64_t *sec, long *nsec)
{
	enum rumpclock rclk = enum_rumpclock;
	struct timespec ts;
	clockid_t clk;

	switch (rclk) {
	case RUMPUSER_CLOCK_RELWALL:
		clk = CLOCK_REALTIME;
		break;
	case RUMPUSER_CLOCK_ABSMONO:
		clk = CLOCK_MONOTONIC;
		break;
	default:
		return EINVAL;
	}

	if (clock_gettime(clk, &ts) == -1) {
		return errno;
	}

	*sec = ts.tv_sec;
	*nsec = ts.tv_nsec;

	return 0;
}

int
rumpuser_clock_sleep(int enum_rumpclock, int64_t sec, long nsec)
{
	enum rumpclock rclk = enum_rumpclock;
	clockid_t clk;

	switch (rclk) {
	case RUMPUSER_CLOCK_RELWALL:
		clk = CLOCK_REALTIME;
		break;
	case RUMPUSER_CLOCK_ABSMONO:
		clk = CLOCK_MONOTONIC;
		break;
	default:
		return EINVAL;
	}

	return clock_sleep(clk, sec, nsec);
}

int
rumpuser_getparam(const char *name, void *buf, size_t blen)
{
	char *value;
	const char *ncpu = "1";

	if (strcmp(name, RUMPUSER_PARAM_NCPU) == 0) {
		strncpy(buf, ncpu, blen);
		return 0;
	}
	if (strcmp(name, RUMPUSER_PARAM_HOSTNAME) == 0) {
		strncpy(buf, "rump", blen);
		return 0;
	}

#ifdef RUMP_MEMLIMIT
#define STRING(s) #s
#define STRINGIFY(x) STRING(x)
	if (strcmp(name, "RUMP_MEMLIMIT") == 0) {
		strncpy(buf, STRINGIFY(RUMP_MEMLIMIT), blen);
		return 0;
	}
#undef STRING
#undef STRINGIFY
#endif

	value = getenv(name);

	if (value != NULL && strlen(value) + 1 <= blen) {
		strncpy(buf, value, blen);
		return 0;
	}

	return EINVAL;
}

void
rumpuser_putchar(int ch)
{
	char c = ch;
	int ret __attribute__ ((unused));

	ret = write(1, &c, 1);
}

__attribute__((__noreturn__)) void
rumpuser_exit(int rv)
{

	if (rv == RUMPUSER_PANIC)
		abort();
	else
		exit(rv);
}

void
rumpuser_seterrno(int error)
{

	errno = error;
}

/*
 * This is meant for safe debugging prints from the kernel.
 */
void
rumpuser_dprintf(const char *format, ...)
{
	va_list ap;
	char buffer[80];
	int ret;
	int size = sizeof(buffer);

	va_start(ap, format);
	ret = vsnprintf(buffer, size, format, ap);
	va_end(ap);
	if (ret >= size)
		buffer[size - 1] = '\0';
	write(2, buffer, strlen(buffer));
}

int
rumpuser_kill(int64_t pid, int sig)
{

	kill(0, sig);

	return 0;
}

int
rumpuser_thread_create(void *(*f)(void *), void *arg, const char *thrname,
        int joinable, int pri, int cpuidx, void **tptr)
{
        struct thread *thr;

        thr = create_thread(thrname, NULL, (void (*)(void *))f, arg, NULL, 0, joinable);

        if (!thr)
                return EINVAL;

        *tptr = thr;
        return 0;
}

void
rumpuser_thread_exit(void)
{

        exit_thread();
}

int
rumpuser_thread_join(void *p)
{

        join_thread(p);
        return 0;
}

/* mtx */

void
rumpuser_mutex_init(struct rumpuser_mtx **mtxp, int flags)
{

	mutex_init(mtxp, flags);
}

void
rumpuser_mutex_enter(struct rumpuser_mtx *mtx)
{

	mutex_enter(mtx);
}

void
rumpuser_mutex_enter_nowrap(struct rumpuser_mtx *mtx)
{

	mutex_enter_nowrap(mtx);
}

int
rumpuser_mutex_tryenter(struct rumpuser_mtx *mtx)
{

	return mutex_tryenter(mtx);
}

void
rumpuser_mutex_exit(struct rumpuser_mtx *mtx)
{

	mutex_exit(mtx);
}

void
rumpuser_mutex_destroy(struct rumpuser_mtx *mtx)
{

	mutex_destroy(mtx);
}

void
rumpuser_mutex_owner(struct rumpuser_mtx *mtx, struct lwp **lp)
{

	mutex_owner(mtx, (void **)lp);
}

void
rumpuser_rw_init(struct rumpuser_rw **rwp)
{

	rw_init(rwp);
}

void
rumpuser_rw_enter(int enum_rumprwlock, struct rumpuser_rw *rw)
{

	rw_enter(enum_rumprwlock, rw);
}

int
rumpuser_rw_tryenter(int enum_rumprwlock, struct rumpuser_rw *rw)
{

	return rw_tryenter(enum_rumprwlock, rw);
}

void
rumpuser_rw_exit(struct rumpuser_rw *rw)
{

	rw_exit(rw);
}

void
rumpuser_rw_destroy(struct rumpuser_rw *rw)
{

	rw_destroy(rw);
}

void
rumpuser_rw_held(int enum_rumprwlock, struct rumpuser_rw *rw, int *rvp)
{

	rw_held(enum_rumprwlock, rw, rvp);
}

void
rumpuser_rw_downgrade(struct rumpuser_rw *rw)
{

	rw_downgrade(rw);
}

int
rumpuser_rw_tryupgrade(struct rumpuser_rw *rw)
{

	return rw_tryupgrade(rw);
}

void
rumpuser_cv_init(struct rumpuser_cv **cvp)
{

	cv_init(cvp);
}

void
rumpuser_cv_destroy(struct rumpuser_cv *cv)
{

	cv_destroy(cv);
}

void
rumpuser_cv_wait(struct rumpuser_cv *cv, struct rumpuser_mtx *mtx)
{

	cv_wait(cv, mtx);
}

void
rumpuser_cv_wait_nowrap(struct rumpuser_cv *cv, struct rumpuser_mtx *mtx)
{

	cv_wait_nowrap(cv, mtx);
}

int
rumpuser_cv_timedwait(struct rumpuser_cv *cv, struct rumpuser_mtx *mtx,
	int64_t sec, int64_t nsec)
{

	return cv_timedwait(cv, mtx, sec, nsec);
}

void
rumpuser_cv_signal(struct rumpuser_cv *cv)
{

	cv_signal(cv);
}

void
rumpuser_cv_broadcast(struct rumpuser_cv *cv)
{

	cv_broadcast(cv);
}

void
rumpuser_cv_has_waiters(struct rumpuser_cv *cv, int *rvp)
{

	cv_has_waiters(cv, rvp);
}

/*
 * curlwp
 */

void
rumpuser_curlwpop(int enum_rumplwpop, struct lwp *l)
{
	enum rumplwpop op = enum_rumplwpop;

	switch (op) {
	case RUMPUSER_LWP_CREATE:
	case RUMPUSER_LWP_DESTROY:
		break;
	case RUMPUSER_LWP_SET:
		set_curlwp(l);
		break;
	case RUMPUSER_LWP_CLEAR:
		assert(curlwp() == l);
		set_curlwp(NULL);
		break;
	}
}

struct lwp *
rumpuser_curlwp(void)
{

	return curlwp();
}
