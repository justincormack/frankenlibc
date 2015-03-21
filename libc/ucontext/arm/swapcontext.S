.global __franken_swapcontext
.type __franken_swapcontext,#function
__franken_swapcontext:
	mov ip,r0
	stmia ip!,{v1,v2,v3,v4,v5,v6,sl,fp,sp,lr}
	mov r0,#0
	/* XXX TODO */
