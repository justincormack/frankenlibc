.global _Reset
_Reset:
	ldr sp, =stack_top
	bl __libc_start_main
	b .
