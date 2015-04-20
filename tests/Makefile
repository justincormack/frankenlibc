RUMPOBJ?=../rumpobj
OBJDIR=$(RUMPOBJ)/tests
RUMPDIR?=../rump
LIBDIR=$(RUMPDIR)/lib
BINDIR=$(RUMPDIR)/bin
INCDIR=$(RUMPDIR)/include
LDFLAGS+=-static
CFLAGS+=-g

DEPS=$(OBJDIR) $(LIBDIR)/libc.a

OBJ=$(OBJDIR)/hello $(OBJDIR)/ctor

default:		test

test:			run

run:			$(OBJ)
			RUMP_VERBOSE=1 ${BINDIR}/rumprun $(OBJDIR)/hello
			${BINDIR}/rumprun $(OBJDIR)/ctor

$(OBJDIR):		
			mkdir -p $(OBJDIR)

$(OBJDIR)/ctor:		ctor.c $(DEPS)
			${CC} ${CFLAGS} ${LDFLAGS} -o $@ ctor.c

$(OBJDIR)/hello:	hello.c $(DEPS)
			${CC} ${CFLAGS} ${LDFLAGS} -o $@ hello.c

.PHONY:			test clean
clean:		
			rm -f $(OBJ)
