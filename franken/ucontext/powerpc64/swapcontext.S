.text
	.global __franken_swapcontext
	.section ".opd","aw"
	.align 3
__franken_swapcontext:
	.quad .__franken_swapcontext,.TOC.@tocbase,0
	.previous
	.global .__franken_swapcontext
.__franken_swapcontext:
	# 0) store IP int 0, then into the jmpbuf pointed to by r3 (first arg)
	mflr 0
	std 0, 0(3)
	# 1) store reg1 (SP)
	std 1, 8(3)
	# 2) store cr
	mfcr 0
	std 0, 16(3)
	# 3) store r14-31
	std 14, 24(3)
	std 15, 32(3)
	std 16, 40(3)
	std 17, 48(3)
	std 18, 56(3)
	std 19, 64(3)
	std 20, 72(3)
	std 21, 80(3)
	std 22, 88(3)
	std 23, 96(3)
	std 24, 104(3)
	std 25, 112(3)
	std 26, 120(3)
	std 27, 128(3)
	std 28, 136(3)
	std 29, 144(3)
	std 30, 152(3)
	std 31, 160(3)
	stfd 14,168(3)
	stfd 15,176(3)
	stfd 16,184(3)
	stfd 17,192(3)
	stfd 18,200(3)
	stfd 19,208(3)
	stfd 20,216(3)
	stfd 21,224(3)
	stfd 22,232(3)
	stfd 23,240(3)
	stfd 24,248(3)
	stfd 25,256(3)
	stfd 26,264(3)
	stfd 27,272(3)
	stfd 28,280(3)
	stfd 29,288(3)
	stfd 30,296(3)
	stfd 31,304(3)

	# 0) move old return address into r0
	ld 0, 0(4)
	# 1) put it into link reg
	mtlr 0
	#2 ) restore stack ptr
	ld 1, 8(4)
	#3) restore control reg
	ld 0, 16(4)
	mtcr 0
	#4) restore r14-r31
	ld 14, 24(4)
	ld 15, 32(4)
	ld 16, 40(4)
	ld 17, 48(4)
	ld 18, 56(4)
	ld 19, 64(4)
	ld 20, 72(4)
	ld 21, 80(4)
	ld 22, 88(4)
	ld 23, 96(4)
	ld 24, 104(4)
	ld 25, 112(4)
	ld 26, 120(4)
	ld 27, 128(4)
	ld 28, 136(4)
	ld 29, 144(4)
	ld 30, 152(4)
	ld 31, 160(4)
	lfd 14,168(4)
	lfd 15,176(4)
	lfd 16,184(4)
	lfd 17,192(4)
	lfd 18,200(4)
	lfd 19,208(4)
	lfd 20,216(4)
	lfd 21,224(4)
	lfd 22,232(4)
	lfd 23,240(4)
	lfd 24,248(4)
	lfd 25,256(4)
	lfd 26,264(4)
	lfd 27,272(4)
	lfd 28,280(4)
	lfd 29,288(4)
	lfd 30,296(4)
	lfd 31,304(4)

	# load return value
	ld 3,312(4)
	# next time return will be zero
	li 5, 0
	std 5,312(4)
	# 5) return
	blr
	nop
