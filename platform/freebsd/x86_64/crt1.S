.text
.global _start
_start:
	andq	$-16,%rsp		/* align stack pointer */
	/* rdi is &argc, argv is (&argc + 8) */
	mov	%rdi, %rdx		/* argv = &argc + 1 */
	add	$0x08, %rdx
	mov	(%rdi), %rsi		/* argc */
	mov	$0, %rdi		/* unused */
	call	_start1
1:	jmp 1b
