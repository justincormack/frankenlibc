.text
.global _start
_start:
	pop	%rsi		/* argc */
	mov	%rsp, %rdx	/* argv */
	push	%rsi
	mov	%rdi, %rcx	/* envp */
	shl	$3, %rcx
	add	$8, %rcx
	add	%rdx, %rcx
	mov	$main,%rdi	/* 1st arg: application entry ip */
	call	__libc_start_main
1:	jmp 1b
