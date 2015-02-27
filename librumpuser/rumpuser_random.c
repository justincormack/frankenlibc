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

#include "rumpuser_port.h"

#include <sys/types.h>

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef HAVE_GETRANDOM
#include <linux/random.h>
#endif

#include <rump/rumpuser.h>

#include "rumpuser_int.h"

static const size_t random_maxread = 32;

#if defined(HAVE_ARC4RANDOM_BUF) || defined(HAVE_GETRANDOM)
int
rumpuser__random_init(void)
{

	return 0;
}
#else
static const char *random_device = "/dev/urandom";
static int random_fd = -1;

int
rumpuser__random_init(void)
{

	random_fd = open(random_device, O_RDONLY);
	if (random_fd < 0) {
		fprintf(stderr, "random init open failed\n");
		return errno;
	}
	return 0;
}
#endif

int
rumpuser_getrandom(void *buf, size_t buflen, int flags, size_t *retp)
{
#ifdef HAVE_ARC4RANDOM_BUF
	buflen = buflen > random_maxread ? random_maxread : buflen;
	arc4random_buf(buf, buflen);
	*retp = buflen;
#elif HAVE_GETRANDOM
	int rv;

	buflen = buflen > random_maxread ? random_maxread : buflen;
	rv = getrandom(buf, buflen, 0);
	if (rv == -1) {
		ET(errno);
	}
	*retp = rv;
#else
	ssize_t rv;

	buflen = buflen > random_maxread ? random_maxread : buflen;
	rv = read(random_fd, buf, buflen);
	if (rv == -1) {
		ET(errno);
	}
	*retp = rv;
#endif

	return 0;
}
