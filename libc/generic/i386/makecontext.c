#include <stdlib.h>
#include <ucontext.h>

void
makecontext(ucontext_t *ucp, void (*fn)(void), int argc, void *arg)
{
	unsigned long stack = (unsigned long) ucp->uc_stack.ss_sp;
	unsigned long stack_size = ucp->uc_stack.ss_size;
	unsigned long *stacktop = (unsigned long *) (stack + stack_size - 12);

	if (argc != 1) abort();

	/* need to push stack pointer, f as ip and data as first arg */
	ucp->uc_regs[4] = stack + stack_size - 16; /* grows down */
	ucp->uc_regs[5] = (unsigned long) fn;
	stacktop[0] = (unsigned long) arg;
}
