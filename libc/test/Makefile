COMPILE.c?=$(CC) -c $(CPPFLAGS) $(CFLAGS)
COMPILE.S?=$(CC) -c $(CPPFLAGS) $(ASFLAGS)
OUTDIR=../../rumpobj/libc-test
LIBDIR=../../rump/lib
FILES=$(OUTDIR)/args $(OUTDIR)/_exit $(OUTDIR)/mmap
INCLUDES=-I../include
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-g -fno-stack-protector
LDFLAGS+=-static -B$(LIBDIR)
LDLIBS=-L$(OUTDIR) -lc -L$(LIBDIR) -lfranken
RANLIB?=ranlib

default:		test

$(OUTDIR):		
			mkdir -p $(OUTDIR)

$(OUTDIR)/linkstub.o:	linkstub.c
			$(COMPILE.c) -o $@ linkstub.c

$(OUTDIR)/libc.a:	$(OUTDIR)/linkstub.o
			$(AR) cr $@ $(OUTDIR)/linkstub.o
			$(RANLIB) $@

$(OUTDIR)/args:		args.c $(OUTDIR)/libc.a
			$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -o $@ args.c $(LDLIBS)

$(OUTDIR)/_exit:	_exit.c $(OUTDIR)/libc.a
			$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -o $@ _exit.c $(LDLIBS)

$(OUTDIR)/mmap:		mmap.c $(OUTDIR)/libc.a
			$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -o $@ mmap.c $(LDLIBS)

.PHONY:			test
test:			$(OUTDIR) $(FILES)
			$(OUTDIR)/args franken rump || exit 1
			$(OUTDIR)/_exit || exit 1
			$(OUTDIR)/mmap || exit 1

.PHONY:			clean
clean:			
			rm -f $(FILES) $(OUTDIR)/*.o $(OUTDIR)/*.a

