#include "rumpuser_port.h"

#include <stdint.h>
#include <stdlib.h>

#include <rump/rumpuser.h>

/*
 * no dynamic linking supported
 */
void
rumpuser_dl_bootstrap(rump_modinit_fn domodinit,
	rump_symload_fn symload, rump_compload_fn compload)
{

	return;
}
