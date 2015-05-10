RUMPOBJ?=../rumpobj
OBJDIR=$(RUMPOBJ)/tests
RUMPDIR?=../rump
LIBDIR=$(RUMPDIR)/lib
BINDIR=$(RUMPDIR)/bin
RE=${BINDIR}/re
INCDIR=$(RUMPDIR)/include
LDFLAGS+=-static
CFLAGS+=-g

DEPS=$(OBJDIR) $(LIBDIR)/libc.a

OBJ=$(OBJDIR)/hello $(OBJDIR)/ctor $(OBJDIR)/cat

default:		test

test:			run

run:			$(OBJ)
			RUMP_VERBOSE=1 ${RE} $(OBJDIR)/hello
			${RE} $(OBJDIR)/ctor
			echo frankenlibc | ${RE} $(OBJDIR)/cat

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
