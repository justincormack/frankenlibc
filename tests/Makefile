RUMP_LIBS_FS?=-lrumpfs_ffs -lrumpfs_cd9660 -lrumpdev_disk -lrumpdev -lrumpvfs
RUMP_LIBS_NET?=-lrumpnet_config -lrumpdev_bpf -lrumpnet_netinet -lrumpnet_netinet6 -lrumpnet_net -lrumpnet
RUMP_LIBS?=-Wl,--whole-archive ${RUMP_LIBS_NET} ${RUMP_LIBS_FS} -lrump -Wl,--no-whole-archive -lrumpuser

LIBDIR=../rump/lib
OBJDIR=../rumpobj/test
BINDIR=../rump/bin
INCDIR=../rump/include

DEPS=$(OBJDIR) $(LIBDIR)/libfranken.a $(LIBDIR)/libc.a $(LIBDIR)/librump.a $(LIBDIR)/librumpuser.a
CPPFLAGS+=-nostdinc -I$(INCDIR)
LDFLAGS+=-static -L$(LIBDIR) -B$(LIBDIR)

LIBS=-Wl,--start-group -lc ${RUMP_LIBS} -lfranken -Wl,--end-group

OBJ=$(OBJDIR)/hello

default:		test

test:			run

run:			$(OBJ)
			RUMP_VERBOSE=1 ${BINDIR}/rumprun $(OBJDIR)/hello

$(OBJDIR):		
			mkdir -p $(OBJDIR)

$(OBJDIR)/hello:	hello.c $(DEPS)
			${CC} -o $@ $(CPPFLAGS) ${CFLAGS} ${LDFLAGS} hello.c $(LIBS)

.PHONY:			test clean
clean:		
			rm $(OBJ)
