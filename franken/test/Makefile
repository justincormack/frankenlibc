COMPILE.c?=$(CC) -c $(CPPFLAGS) $(CFLAGS)
COMPILE.S?=$(CC) -c $(CPPFLAGS) $(ASFLAGS)
RUMPOBJ?=../../rumpobj
OUTDIR=$(RUMPOBJ)/libc-test
RUMP?=$(RUMPOBJ)/rump
LIBDIR=$(RUMP)/lib
FILES=$(OUTDIR)/args $(OUTDIR)/env $(OUTDIR)/_exit $(OUTDIR)/mmap
INCLUDES=-I../include -I../../platform/include
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-g -fno-stack-protector
LDFLAGS+=-static -B$(LIBDIR)
LDLIBS=-Wl,--start-group -L$(OUTDIR) -lc -L$(LIBDIR) -lfranken -lplatform -Wl,--end-group
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
			$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(LDSTATIC) -o $@ args.c $(LDLIBS)

$(OUTDIR)/env:		env.c $(OUTDIR)/libc.a
			$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(LDSTATIC) -o $@ env.c $(LDLIBS)

$(OUTDIR)/_exit:	_exit.c $(OUTDIR)/libc.a
			$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(LDSTATIC) -o $@ _exit.c $(LDLIBS)

$(OUTDIR)/mmap:		mmap.c $(OUTDIR)/libc.a
			$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(LDSTATIC) -o $@ mmap.c $(LDLIBS)

.PHONY:			test
test:			$(OUTDIR) $(FILES)
			$(OUTDIR)/args franken rump
			FRANKEN=RUMP $(OUTDIR)/env
			$(OUTDIR)/_exit
			$(OUTDIR)/mmap

.PHONY:			clean
clean:			
			rm -f $(FILES) $(OUTDIR)/*.o $(OUTDIR)/*.a

