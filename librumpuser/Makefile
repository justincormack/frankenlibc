
# rumpuser.h is in sys/rump for inclusion by kernel components
#.PATH:		${.CURDIR}/../../sys/rump/include/rump

LIB=		../rump/lib/librumpuser.a

CPPFLAGS+=	-DLIBRUMPUSER

SRCS=		rumpfiber.c
SRCS+=		rumpfiber_sp.c
SRCS+=		rumpuser_component.c rumpuser_random.c
SRCS+=		rumpuser_file_dummy.c rumpuser_mem.c
SRCS+=		rumpuser_errtrans.c rumpuser_sigtrans.c
SRCS+=		rumpuser_dl.c rumpuser_daemonize_dummy.c

INCS=		rumpuser_component.h rumpuser_port.h

OBJDIR=../rumpobj/librumpuser

DEPS=$(INCS) $(OBJDIR)
# do not include libc include here?
CPPFLAGS+=-nostdinc -I. -I../libc/include -I../rump/include
CFLAGS+=-fno-stack-protector

OBJS=$(OBJDIR)/rumpfiber.o
OBJS+=$(OBJDIR)/rumpuser_mem.o $(OBJDIR)/rumpuser_random.o
OBJS+=$(OBJDIR)/rumpuser_component.o
# not really required
OBJS+=$(OBJDIR)/rumpuser_errtrans.o $(OBJDIR)/rumpuser_sigtrans.o
# dummy
OBJS+=$(OBJDIR)/rumpfiber_sp.o $(OBJDIR)/rumpuser_file_dummy.o
OBJS+=$(OBJDIR)/rumpuser_daemonize_dummy.o $(OBJDIR)/rumpuser_dl.o

default:			$(OBJDIR) $(LIB)

$(OBJDIR):			
				mkdir -p $(OBJDIR)

$(LIB):				$(OBJS)
				$(AR) cr $@ $(OBJS)

$(OBJDIR)/rumpfiber.o:		rumpfiber.c $(DEPS)
				$(COMPILE.c) -o $@ rumpfiber.c

$(OBJDIR)/rumpuser_mem.o:	rumpuser_mem.c $(DEPS)
				$(COMPILE.c) -o $@ rumpuser_mem.c

$(OBJDIR)/rumpuser_random.o:	rumpuser_random.c $(DEPS)
				$(COMPILE.c) -o $@ rumpuser_random.c

$(OBJDIR)/rumpuser_component.o:	rumpuser_component.c $(DEPS)
				$(COMPILE.c) -o $@ rumpuser_component.c

$(OBJDIR)/rumpuser_errtrans.o:	rumpuser_errtrans.c $(DEPS)
				$(COMPILE.c) -o $@ rumpuser_errtrans.c

$(OBJDIR)/rumpuser_sigtrans.o:	rumpuser_sigtrans.c $(DEPS)
				$(COMPILE.c) -o $@ rumpuser_sigtrans.c

$(OBJDIR)/rumpfiber_sp.o:	rumpfiber_sp.c $(DEPS)
				$(COMPILE.c) -o $@ rumpfiber_sp.c

$(OBJDIR)/rumpuser_file_dummy.o:	rumpuser_file_dummy.c $(DEPS)
				$(COMPILE.c) -o $@ rumpuser_file_dummy.c

$(OBJDIR)/rumpuser_daemonize_dummy.o:	rumpuser_daemonize_dummy.c $(DEPS)
				$(COMPILE.c) -o $@ rumpuser_daemonize_dummy.c

$(OBJDIR)/rumpuser_dl.o:	rumpuser_dl.c $(DEPS)
				$(COMPILE.c) -o $@ rumpuser_dl.c

.PHONY:				clean
clean:				
				rm -f $(OBJS) $(LIB)
