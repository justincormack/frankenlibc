.global swapcontext
.type swapcontext,@function
swapcontext:
	mov %rbx,(%rdi)		/* first buffer (prev) */
	mov %rbp,8(%rdi)
	mov %r12,16(%rdi)
	mov %r13,24(%rdi)
	mov %r14,32(%rdi)
	mov %r15,40(%rdi)
	lea 8(%rsp),%rdx	/* this is our rsp WITHOUT current ret addr */
	mov %rdx,48(%rdi)
	mov (%rsp),%rdx		/* save return addr ptr for new rip */
	mov %rdx,56(%rdi)

	mov (%rsi),%rbx		/* second buffer (next) */
	mov 8(%rsi),%rbp
	mov 16(%rsi),%r12
	mov 24(%rsi),%r13
	mov 32(%rsi),%r14
	mov 40(%rsi),%r15
	mov 48(%rsi),%rdx	/* this ends up being the stack pointer */
	mov %rdx,%rsp
	mov 56(%rsi),%rdx	/* this is the instruction pointer */

	mov 64(%rsi), %rdi	/* load initial argument into rdi */

	jmp *%rdx		/* goto saved address without altering rsp */
