#include <stdlib.h>
#include <ucontext.h>

void
makecontext(ucontext_t *ucp, void (*fn)(void), int argc, void *arg)
{
	unsigned long stack = (unsigned long) ucp->uc_stack.ss_sp;
	unsigned long stack_size = ucp->uc_stack.ss_size;

	if (argc != 1) abort();

	/* need to push stack pointer, f as ip and data as first arg */
	ucp->uc_regs[1] = stack + stack_size - 16; /* grows down */
	/* address is first pointer in function descriptor */
	ucp->uc_regs[0] = (unsigned long) (*(unsigned long *)fn);
	ucp->uc_regs[39] = (unsigned long) arg;
}
