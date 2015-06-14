COMPILE.c?=$(CC) -c $(CPPFLAGS) $(CFLAGS)
COMPILE.S?=$(CC) -c $(CPPFLAGS) $(ASFLAGS)
RUMPOBJ?=../../rumpobj
OUTDIR=$(RUMPOBJ)/franken-test
STUBLIBCDIR=$(RUMPOBJ)/stublibc
RUMP?=$(RUMPOBJ)/rump
LIBDIR=$(RUMP)/lib
FILES=$(OUTDIR)/args $(OUTDIR)/env $(OUTDIR)/_exit $(OUTDIR)/mmap
INCLUDES=-I../include -I../../platform/include
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-g -fno-stack-protector
LDFLAGS+=-static -B$(LIBDIR)
LDLIBS=-Wl,--start-group -L$(STUBLIBCDIR) -lc -L$(LIBDIR) -lfranken -lplatform -Wl,--end-group
DEPS=

default:		test

$(OUTDIR)/args:		args.c $(DEPS)
			@mkdir -p $(OUTDIR)
			$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(LDSTATIC) -o $@ args.c $(LDLIBS)

$(OUTDIR)/env:		env.c $(DEPS)
			@mkdir -p $(OUTDIR)
			$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(LDSTATIC) -o $@ env.c $(LDLIBS)

$(OUTDIR)/_exit:	_exit.c $(DEPS)
			@mkdir -p $(OUTDIR)
			$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(LDSTATIC) -o $@ _exit.c $(LDLIBS)

$(OUTDIR)/mmap:		mmap.c $(DEPS)
			@mkdir -p $(OUTDIR)
			$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(LDSTATIC) -o $@ mmap.c $(LDLIBS)

.PHONY:			test
test:			$(FILES)
			@mkdir -p $(OUTDIR)
			$(OUTDIR)/args franken rump
			FRANKEN=RUMP $(OUTDIR)/env
			$(OUTDIR)/_exit
			$(OUTDIR)/mmap

.PHONY:			clean
clean:			
			rm -f $(FILES) $(OUTDIR)/*.o
