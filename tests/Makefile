RUMPOBJ?=../rumpobj
OBJDIR=$(RUMPOBJ)/test
OUTDIR?=../rump
LIBDIR=$(OUTDIR)/lib
BINDIR=$(OUTDIR)/bin
INCDIR=$(OUTDIR)/include

DEPS=$(OBJDIR) $(LIBDIR)/libc.a
CPPFLAGS+=-nostdinc -I$(INCDIR)
LDFLAGS+=-static -L$(LIBDIR) -B$(LIBDIR)

OBJ=$(OBJDIR)/hello

default:		test

test:			run

run:			$(OBJ)
			RUMP_VERBOSE=1 ${BINDIR}/rumprun $(OBJDIR)/hello

$(OBJDIR):		
			mkdir -p $(OBJDIR)

$(OBJDIR)/hello:	hello.c $(DEPS)
			${CC} -o $@ $(CPPFLAGS) ${CFLAGS} ${LDFLAGS} hello.c

.PHONY:			test clean
clean:		
			rm -f $(OBJ)
