/*	$NetBSD: virtif_user.c,v 1.3 2014/03/14 10:06:22 pooka Exp $	*/

/*
 * Copyright (c) 2013 Antti Kantee.  All Rights Reserved.
 * Copyright (c) 2015 Justin Cormack.  All Rights Reserved.
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

#ifndef _KERNEL
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "rumpuser_component.h"
#include "thread.h"
#include "init.h"

#include "if_virt.h"
#include "virtif_user.h"

#if VIFHYPER_REVISION != 20140313
#error VIFHYPER_REVISION mismatch
#endif

struct virtif_user {
	struct virtif_sc *viu_virtifsc;
	struct thread *viu_rcvthr;
	int viu_devnum;
	int viu_fd;
	int viu_dying;
	char viu_rcvbuf[9018] __attribute__ ((aligned (16))); /* jumbo frame max len */
};

static void
rcvthread(void *arg)
{
	struct virtif_user *viu = arg;
	struct iovec iov;
	size_t nn = 0;

	rumpuser_component_kthread();

	while (!viu->viu_dying) {

		nn = read(viu->viu_fd,
			viu->viu_rcvbuf, sizeof(viu->viu_rcvbuf));
		if (nn == -1 && errno == EAGAIN) {
			rumpuser_component_schedule(NULL);
			/* XXX temporary until we do interrupts properly */
			/* schedule(); */
			clock_sleep(CLOCK_MONOTONIC, 0, 1000);
			rumpuser_component_unschedule();
			continue;
		}
		if (nn == -1) {
			break; /* XXX decide what to do on error */
		}
		iov.iov_base = viu->viu_rcvbuf;
		iov.iov_len = nn;

		rumpuser_component_schedule(NULL);
		VIF_DELIVERPKT(viu->viu_virtifsc, &iov, 1);
		rumpuser_component_unschedule();
	}

	assert(viu->viu_dying);

	rumpuser_component_kthread_release();
}

/* XXX hack, work out better way */
int
rumpns_virt_hwaddr(char *ifname, uint8_t hwaddr[6])
{
	int ret, fd;
	struct stat st;

	if (strlen(ifname) < 5 || strncmp(ifname, "virt", 4) != 0)
		return -1;
	fd = atoi(&ifname[4]);

	memcpy(hwaddr, __franken_fd[fd].st.st_hwaddr, 6);

	return 0;
}

int
VIFHYPER_CREATE(const char *devstr, struct virtif_sc *vif_sc, uint8_t *enaddr,
	struct virtif_user **viup)
{
	struct virtif_user *viu = NULL;
	void *cookie;
	int devnum;
	int rv;

	cookie = rumpuser_component_unschedule();

	/*
	 * Since this interface doesn't do LINKSTR, we know devstr to be
	 * well-formatted.
	 */
	devnum = atoi(devstr);

	viu = calloc(1, sizeof(*viu));
	if (viu == NULL) {
		rv = errno;
		goto oerr1;
	}
	viu->viu_virtifsc = vif_sc;

	viu->viu_fd = devnum;
	viu->viu_devnum = devnum;

	viu->viu_rcvthr = create_thread(devstr, NULL, rcvthread, viu, NULL, 0, 1);
	if (! viu->viu_rcvthr)
		goto oerr2;

	rumpuser_component_schedule(cookie);
	*viup = viu;
	return 0;

 oerr2:
	free(viu);
 oerr1:
	rumpuser_component_schedule(cookie);
	return rumpuser_component_errtrans(rv);
}

void
VIFHYPER_SEND(struct virtif_user *viu,
	struct iovec *iov, size_t iovlen)
{
	void *cookie = rumpuser_component_unschedule();
	ssize_t ret __attribute__((__unused__));

	/* packets may be dropped */
	ret = writev(viu->viu_fd, iov, iovlen);

	rumpuser_component_schedule(cookie);
}

int
VIFHYPER_DYING(struct virtif_user *viu)
{

	/* this may take a while to pick up
	   should perhaps make process scheduled */
	viu->viu_dying = 1;

	return 0;
}

void
VIFHYPER_DESTROY(struct virtif_user *viu)
{
	void *cookie = rumpuser_component_unschedule();

	join_thread(viu->viu_rcvthr);
	free(viu);

	rumpuser_component_schedule(cookie);
}
#endif
