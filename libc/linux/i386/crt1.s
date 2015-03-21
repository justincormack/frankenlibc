.weak _init
.weak _fini
.text
.global _start
_start:
	xor %ebp,%ebp
	pop %ecx
	mov %esp,%eax
	and $-16,%esp
	push %esp
	push %esp
	push %edx
	push $_fini
	push $_init
	push %eax
	push %ecx
	push $main
	call __platform_init
1:	jmp 1b
