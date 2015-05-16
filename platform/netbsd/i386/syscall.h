#define xstr(s) str(s)
#define str(s) #s

#define SYSCALL(sc, name) \
__asm__(" \n\
.global " #name "; \n\
.type " #name ",@function; \n\
" #name ":; \n\
	mov	$" xstr(SYS_ ## sc) ", %eax; \n\
	int	$0x80; \n\
	jnc	" xstr(_syscall_return_ ## sc) "; \n\
	mov	%eax, errno; \n\
	mov	$-1, %eax; \n\
" xstr(_syscall_return_ ## sc) ":; \n\
	ret; \n\
");
