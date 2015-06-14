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

#include "rumpuser_port.h"

#include <sys/mman.h>

#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include <rump/rumpuser.h>

#include "rumpuser_int.h"

static size_t pagesize = 0;

int
rumpuser_malloc(size_t size, int alignment, void **memp)
{
	void *mem;
	int af = 0;
	int sizevoid = sizeof(void *);

	pagesize = (pagesize == 0) ? (size_t)getpagesize() : pagesize;

	if (size < pagesize) {
		if (alignment < sizevoid)
			alignment = sizevoid;
		return posix_memalign(memp, alignment, size);
	}

	while (alignment > 1) {
		alignment >>= 1;
		af++;
	}

	mem = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON | MAP_ALIGNED(af), -1, 0);
	if (mem == MAP_FAILED) {
		return EINVAL;
	}

	*memp = mem;

	return 0;
}

void
rumpuser_free(void *ptr, size_t size)
{

	if (size < pagesize)
		free(ptr);
	else
		munmap(ptr, size);
}

int
rumpuser_anonmmap(void *prefaddr, size_t size, int alignbit, int exec, void **memp)
{
	void *mem;
	int prot = PROT_READ | PROT_WRITE | (exec ? PROT_EXEC : 0);

	mem = mmap(prefaddr, size, prot,
	    MAP_PRIVATE | MAP_ANON | MAP_ALIGNED(alignbit), -1, 0);

	if (mem == MAP_FAILED) {
		return errno;
	}

	*memp = mem;

	return 0;
}

void
rumpuser_unmap(void *addr, size_t len)
{

	munmap(addr, len);
}
