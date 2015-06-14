RUMPOBJ?=../rumpobj
OBJDIR=$(RUMPOBJ)/tests
RUMPDIR?=../rump
LIBDIR=$(RUMPDIR)/lib
BINDIR?=$(RUMPDIR)/bin
REXEC=${BINDIR}/rexec
INCDIR=$(RUMPDIR)/include
LDFLAGS+=-static
CFLAGS+=-g

DEPS=$(OBJDIR) $(LIBDIR)/libc.a

OBJ=$(OBJDIR)/hello $(OBJDIR)/ctor $(OBJDIR)/cat

default:		$(OBJ)

run:			$(OBJ)
			RUMP_VERBOSE=1 ${REXEC} $(OBJDIR)/hello
			${REXEC} $(OBJDIR)/ctor
			echo frankenlibc | ${REXEC} $(OBJDIR)/cat

$(OBJDIR):		
			mkdir -p $(OBJDIR)

$(OBJDIR)/ctor:		ctor.c $(DEPS)
			${CC} ${CFLAGS} ${LDFLAGS} -o $@ ctor.c

$(OBJDIR)/hello:	hello.c $(DEPS)
			${CC} ${CFLAGS} ${LDFLAGS} -o $@ hello.c

$(OBJDIR)/cat:		cat.c $(DEPS)
			${CC} ${CFLAGS} ${LDFLAGS} -o $@ cat.c

.PHONY:			test clean
clean:		
			rm -f $(OBJ)
