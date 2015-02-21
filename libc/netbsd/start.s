.section ".note.netbsd.ident", "a"
	.p2align 2

	.long   7
	.long   4
	.long   1
	.ascii  "NetBSD\0\0"
	.long   600000000	/* requires NetBSD 6.0 */
	.previous
	.p2align 2
