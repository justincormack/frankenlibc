.global __franken_swapcontext
.type __franken_swapcontext,@function
__franken_swapcontext:
	mov  4(%esp), %eax
	mov     %ebx, (%eax)
	mov     %esi, 4(%eax)
	mov     %edi, 8(%eax)
	mov     %ebp, 12(%eax)
	lea  4(%esp), %ecx	/* this is our rsp WITHOUT current ret addr */
	mov     %ecx, 16(%eax)
	mov   (%esp), %ecx	/* save return addr ptr for new rip */
	mov     %ecx, 20(%eax)

	mov  8(%esp), %eax
	mov   (%eax), %ebx
	mov  4(%eax), %esi
	mov  8(%eax), %edi
	mov 12(%eax), %ebp
	mov 16(%eax), %ecx	/* this ends up being the stack pointer */
	mov     %ecx, %esp
	mov 20(%eax), %ecx      /* this is the instruction pointer */
	mov 24(%eax), %edx	/* initial argument */
	push    %edx

	xor     %eax, %eax	/* zero return value */
	jmp    *%ecx
