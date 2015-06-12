LIB=	franken_tc

SRCS+=	franken_tc.c

RUMPTOP= ${TOPRUMP}

#CPPFLAGS+=	-I${RUMPTOP}/librump/rumpkern -I${RUMPTOP}/librump
CPPFLAGS+=	-I${.CURDIR} -I${.CURDIR}/../src/sys/
CPPFLAGS+=	-D__RUMP_KERNEL__

RUMP_SYM_NORENAME=__platform_clock_

.include "${RUMPTOP}/Makefile.rump"
.include <bsd.lib.mk>
.include <bsd.klinks.mk>
