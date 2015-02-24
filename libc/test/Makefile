OUTDIR=../../obj/libc-test
LIBDIR=../../rump/lib
FILES=$(OUTDIR)/_exit $(OUTDIR)/mmap
INCLUDES=-I../include
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-g -fno-stack-protector
LDFLAGS=-static -B$(LIBDIR)
LDLIBS=$(OUTDIR)/linkstub.o -L$(LIBDIR) -lfranken

default:		test

$(OUTDIR):		
			mkdir -p $(OUTDIR)

$(OUTDIR)/linkstub.o:	linkstub.c
			$(COMPILE.c) -o $@ linkstub.c

$(OUTDIR)/_exit:	_exit.c $(OUTDIR)/linkstub.o
			$(LINK.c) -o $@ _exit.c $(LDLIBS)

$(OUTDIR)/mmap:		mmap.c $(OUTDIR)/linkstub.o
			$(LINK.c) -o $@ mmap.c $(LDLIBS)

.PHONY:			test
test:			$(OUTDIR) $(FILES)
			$(OUTDIR)/_exit || exit 1
			$(OUTDIR)/mmap || exit 1

.PHONY:			clean
clean:			
			rm -f $(FILES) $(OUTDIR)/linkstub.o

