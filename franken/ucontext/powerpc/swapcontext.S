.global __franken_swapcontext
.type __franken_swapcontext,@function
__franken_swapcontext:
	# 0) store IP int 0, then into the jmpbuf pointed to by r3 (first arg)
	mflr 0
	stw 0, 0(3)
	# 1) store reg1 (SP)
	stw 1, 4(3)
	# 2) store cr
	mfcr 0
	stw 0, 8(3)
	# 3) store r14-31
	stw 14, 12(3)
	stw 15, 16(3)
	stw 16, 20(3)
	stw 17, 24(3)
	stw 18, 28(3)
	stw 19, 32(3)
	stw 20, 36(3)
	stw 21, 40(3)
	stw 22, 44(3)
	stw 23, 48(3)
	stw 24, 52(3)
	stw 25, 56(3)
	stw 26, 60(3)
	stw 27, 64(3)
	stw 28, 68(3)
	stw 29, 72(3)
	stw 30, 76(3)
	stw 31, 80(3)
	stfd 14,88(3)
	stfd 15,96(3)
	stfd 16,104(3)
	stfd 17,112(3)
	stfd 18,120(3)
	stfd 19,128(3)
	stfd 20,136(3)
	stfd 21,144(3)
	stfd 22,152(3)
	stfd 23,160(3)
	stfd 24,168(3)
	stfd 25,176(3)
	stfd 26,184(3)
	stfd 27,192(3)
	stfd 28,200(3)
	stfd 29,208(3)
	stfd 30,216(3)
	stfd 31,224(3)

	# 0) move old return address into r0
	lwz 0, 0(4)
	# 1) put it into link reg
	mtlr 0
	#2 ) restore stack ptr
	lwz 1, 4(4)
	#3) restore control reg
	lwz 0, 8(4)
	mtcr 0
	#4) restore r14-r31
	lwz 14, 12(4)
	lwz 15, 16(4)
	lwz 16, 20(4)
	lwz 17, 24(4)
	lwz 18, 28(4)
	lwz 19, 32(4)
	lwz 20, 36(4)
	lwz 21, 40(4)
	lwz 22, 44(4)
	lwz 23, 48(4)
	lwz 24, 52(4)
	lwz 25, 56(4)
	lwz 26, 60(4)
	lwz 27, 64(4)
	lwz 28, 68(4)
	lwz 29, 72(4)
	lwz 30, 76(4)
	lwz 31, 80(4)
	lfd 14,88(4)
	lfd 15,96(4)
	lfd 16,104(4)
	lfd 17,112(4)
	lfd 18,120(4)
	lfd 19,128(4)
	lfd 20,136(4)
	lfd 21,144(4)
	lfd 22,152(4)
	lfd 23,160(4)
	lfd 24,168(4)
	lfd 25,176(4)
	lfd 26,184(4)
	lfd 27,192(4)
	lfd 28,200(4)
	lfd 29,208(4)
	lfd 30,216(4)
	lfd 31,224(4)

	# load return value
	lfd 3,232(4)
	# next time return will be zero
	li 5, 0
	stfd 5,232(4)
	# 5) return
	blr
