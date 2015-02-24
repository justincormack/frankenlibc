OUTDIR=../../obj/libc-test
LIBDIR=../../rump/lib
FILES=$(OUTDIR)/_exit $(OUTDIR)/mmap
INCLUDES=-I../include
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-g -fno-stack-protector -nostdlib
LDFLAGS=-static -B$(LIBDIR)
LDLIBS=$(OUTDIR)/linkstub.o -L$(LIBDIR) -lfranken

default:		test

$(OUTDIR):		
			mkdir -p $(OUTDIR)

$(OUTDIR)/linkstub.o:	linkstub.c
			$(COMPILE.c) -o $@ linkstub.c

$(OUTDIR)/_exit.o:	_exit.c
			$(COMPILE.c) -o $@ _exit.c

$(OUTDIR)/_exit:	$(OUTDIR)/_exit.o $(OUTDIR)/linkstub.o
			$(LINK.o) -o $@ $(OUTDIR)/_exit.o $(LDLIBS)

$(OUTDIR)/mmap.o:	mmap.c
			$(COMPILE.c) -o $@ mmap.c

$(OUTDIR)/mmap:		$(OUTDIR)/mmap.o $(OUTDIR)/linkstub.o
			$(LINK.o) -o $@ $(OUTDIR)/mmap.o $(LDLIBS)

.PHONY:			test
test:			$(OUTDIR) $(FILES)
			$(OUTDIR)/_exit || exit 1
			$(OUTDIR)/mmap || exit 1

.PHONY:			clean
clean:			
			rm -f $(FILES) $(OUTDIR)/linkstub.o

