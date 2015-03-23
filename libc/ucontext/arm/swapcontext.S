.global __franken_swapcontext
.type __franken_swapcontext,#function
__franken_swapcontext:
	mov r3,r1 /* buffer to swap to */

	mov ip,r0
	stmia ip!,{v1,v2,v3,v4,v5,v6,sl,fp,sp,lr}

	adr r1,1f
	ldr r2,1f
	ldr r1,[r1,r2]

	tst r1,#0x260
	beq 3f
	tst r1,#0x20
	beq 2f
	stc p2, cr4, [ip], #48
2:	tst r1,#0x40
	beq 2f
	.word 0xecac8b10 /* vstmia ip!, {d8-d15} */
2:	tst r1,#0x200
	beq 3f
	stcl p1, cr10, [ip], #8
	stcl p1, cr11, [ip], #8
	stcl p1, cr12, [ip], #8
	stcl p1, cr13, [ip], #8
	stcl p1, cr14, [ip], #8
	stcl p1, cr15, [ip], #8

3:	mov ip,r3 /* saved second arg, buffer to restore */
	ldr r0,[ip, #128] /* initial arg */
	mov r2,#0
	str r2,[ip, #128] /* zero initial arg */

	ldmia ip!, {v1,v2,v3,v4,v5,v6,sl,fp,sp,lr}

	adr r1,1f
	ldr r2,1f
	ldr r1,[r1,r2]

	tst r1,#0x260
	beq 3f
	tst r1,#0x20
	beq 2f
	ldc p2, cr4, [ip], #48
2:	tst r1,#0x40
	beq 2f
	.word 0xecbc8b10 /* vldmia ip!, {d8-d15} */
2:	tst r1,#0x200
	beq 3f
	ldcl p1, cr10, [ip], #8
	ldcl p1, cr11, [ip], #8
	ldcl p1, cr12, [ip], #8
	ldcl p1, cr13, [ip], #8
	ldcl p1, cr14, [ip], #8
	ldcl p1, cr15, [ip], #8
3:	tst lr,#1
	moveq pc,lr
	bx lr

.hidden __hwcap
1:	.word __hwcap-1b
