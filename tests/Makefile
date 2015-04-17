RUMPOBJ?=../rumpobj
OBJDIR=$(RUMPOBJ)/tests
OUTDIR?=../rump
LIBDIR=$(OUTDIR)/lib
BINDIR=$(OUTDIR)/bin
INCDIR=$(OUTDIR)/include

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
			${CC} -o $@ ctor.c

$(OBJDIR)/hello:	hello.c $(DEPS)
			${CC} -o $@ hello.c

.PHONY:			test clean
clean:		
			rm -f $(OBJ)
