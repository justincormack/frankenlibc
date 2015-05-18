.global __franken_swapcontext
.type __franken_swapcontext,@function
__franken_swapcontext:

	mv t0, a1

	sd ra, (a0)
	sd ra, (1 * 8)(a0)
	sd sp, (2 * 8)(a0)
	sd s0, (3 * 8)(a0)
	sd s1, (4 * 8)(a0)
	sd s2, (5 * 8)(a0)
	sd s3, (6 * 8)(a0)
	sd s4, (7 * 8)(a0)
	sd s5, (8 * 8)(a0)
	sd s6, (9 * 8)(a0)
	sd s7, (10 * 8)(a0)
	sd s8, (11 * 8)(a0)
	sd s9, (12 * 8)(a0)
	sd s10, (13 * 8)(a0)
	sd s11, (14 * 8)(a0)

	sd x0, (15 * 8)(a0) /* 0 ret val */

#ifdef __riscv_hard_float
	frsr a1

	fsd fs0, (16 * 8)(a0)
	fsd fs1, (17 * 8)(a0)
	fsd fs2, (18 * 8)(a0)
	fsd fs3, (19 * 8)(a0)
	fsd fs4, (20 * 8)(a0)
	fsd fs5, (21 * 8)(a0)
	fsd fs6, (22 * 8)(a0)
	fsd fs7, (23 * 8)(a0)
	fsd fs8, (24 * 8)(a0)
	fsd fs9, (25 * 8)(a0)
	fsd fs10, (26 * 8)(a0)
	fsd fs11, (27 * 8)(a0)

	sw a1, (28 * 8)(a0)

	lw t1, (28 * 8)(t0)

	fld fs0, (16 * 8)(t0)
	fld fs1, (17 * 8)(t0)
	fld fs2, (18 * 8)(t0)
	fld fs3, (19 * 8)(t0)
	fld fs4, (20 * 8)(t0)
	fld fs5, (21 * 8)(t0)
	fld fs6, (22 * 8)(t0)
	fld fs7, (23 * 8)(t0)
	fld fs8, (24 * 8)(t0)
	fld fs9, (25 * 8)(t0)
	fld fs10, (26 * 8)(t0)
	fld fs11, (27 * 8)(t0)

	fssr t1
#endif

	ld t1, (t0)
	ld ra, (1 * 8)(t0)
	ld sp, (2 * 8)(t0)
	ld s0, (3 * 8)(t0)
	ld s1, (4 * 8)(t0)
	ld s2, (5 * 8)(t0)
	ld s3, (6 * 8)(t0)
	ld s4, (7 * 8)(t0)
	ld s5, (8 * 8)(t0)
	ld s6, (9 * 8)(t0)
	ld s7, (10 * 8)(t0)
	ld s8, (11 * 8)(t0)
	ld s9, (12 * 8)(t0)
	ld s10, (13 * 8)(t0)
	ld s11, (14 * 8)(t0)
	ld a0, (15 * 8)(t0)

	jr t1
