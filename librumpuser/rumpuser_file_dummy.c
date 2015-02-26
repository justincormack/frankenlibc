/*
 * Copyright (c) 2007-2010 Antti Kantee.  All Rights Reserved.
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

/* NOTE this code will move to a new driver in the next hypercall revision */

#include "rumpuser_port.h"

#if !defined(lint)
__RCSID("$NetBSD: rumpuser_file.c,v 1.1 2014/07/09 23:41:40 justin Exp $");
#endif /* !lint */

#include <errno.h>
#include <stdint.h>
#include <stdlib.h>

#include <rump/rumpuser.h>

#include "rumpuser_int.h"

int
rumpuser_getfileinfo(const char *path, uint64_t *sizep, int *ftp)
{

	ET(ENOENT);
}

int
rumpuser_open(const char *path, int ruflags, int *fdp)
{

	ET(ENOENT);
}

int
rumpuser_close(int fd)
{

	ET(EBADF);
}

int
rumpuser_iovread(int fd, struct rumpuser_iovec *ruiov, size_t iovlen,
	int64_t roff, size_t *retp)
{

	ET(EBADF);
}

int
rumpuser_iovwrite(int fd, const struct rumpuser_iovec *ruiov, size_t iovlen,
	int64_t roff, size_t *retp)
{

	ET(EBADF);
}

int
rumpuser_syncfd(int fd, int flags, uint64_t start, uint64_t len)
{

	ET(EBADF);
}

void
rumpuser_bio(int fd, int op, void *data, size_t dlen, int64_t doff,
        rump_biodone_fn biodone, void *bioarg)
{

	biodone(bioarg, (size_t)0, EBADF); /* convert error no */
}
