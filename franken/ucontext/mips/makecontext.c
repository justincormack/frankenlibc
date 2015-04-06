#include <stdlib.h>
#include <ucontext.h>

void
makecontext(ucontext_t *ucp, void (*fn)(void), int argc, void *arg)
{
	unsigned long stack = (unsigned long) ucp->uc_stack.ss_sp;
	unsigned long stack_size = ucp->uc_stack.ss_size;
	register int gs __asm__ ("$28");

	if (argc != 1) abort();

	/* need to push stack pointer, f as ip and data as first arg */
	ucp->uc_regs[1] = stack + stack_size - 8; /* grows down */
	ucp->uc_regs[0] = (unsigned long) fn;
	ucp->uc_regs[10] = ucp->uc_regs[1]; /* frame pointer */
	ucp->uc_regs[11] = gs; /* gs */
	ucp->uc_regs[26] = (unsigned long) arg;
}
