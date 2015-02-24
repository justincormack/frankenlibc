OUTDIR=../../obj/libc-test
LIBDIR=../../rump/lib
FILES=$(OUTDIR)/_exit $(OUTDIR)/mmap
INCLUDES=-I../include
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-g -fno-stack-protector -nostdlib -L$(LIBDIR)
# XXX fix this up when we have a better build process
LINK1=$(CC) $(CPPFLAGS) $(CFLAGS) -L${LIBDIR} ${LIBDIR}/crt1.o ${LIBDIR}/crti.o
LINK2=-lfranken $(OUTDIR)/linkstub.o $(LIBDIR)/crtn.o

default:		test

$(OUTDIR):		
			mkdir -p $(OUTDIR)

$(OUTDIR)/linkstub.o:	linkstub.c
			$(COMPILE.c) -o $@ linkstub.c

$(OUTDIR)/_exit:	_exit.c $(OUTDIR)/linkstub.o
			$(LINK1) -o $@ _exit.c $(LINK2)

$(OUTDIR)/mmap:		mmap.c $(OUTDIR)/linkstub.o
			$(LINK1) -o $@ mmap.c $(LINK2)

.PHONY:			test
test:			$(OUTDIR) $(FILES)
			$(OUTDIR)/_exit || exit 1
			$(OUTDIR)/mmap || exit 1

.PHONY:			clean
clean:			
			rm -f $(FILES) $(OUTDIR)/linkstub.o

