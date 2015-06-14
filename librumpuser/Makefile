COMPILE.c?=$(CC) -c $(CPPFLAGS) $(CFLAGS)

RUMPOBJ?=../rumpobj
RUMP?=$(RUMPOBJ)/rump
LIBLIB=$(RUMP)/lib
LIB=$(LIBLIB)/librumpuser.a

CPPFLAGS+=-DLIBRUMPUSER

INCS=rumpuser_component.h rumpuser_port.h

OBJDIR=$(RUMPOBJ)/librumpuser

DEPS=$(INCS)
INCLUDE=-I. -I../franken/include -I../franken/ucontext -I../franken/thread -I../franken/init -I../platform/include
CPPFLAGS+=-nostdinc $(INCLUDE)
CFLAGS+=-fno-stack-protector

OBJS=$(OBJDIR)/rumpuser.o
OBJS+=$(OBJDIR)/rumpuser_mem.o $(OBJDIR)/rumpuser_random.o
OBJS+=$(OBJDIR)/rumpuser_component.o

OBJS+=$(OBJDIR)/rumpuser_sp.o $(OBJDIR)/rumpuser_file.o
OBJS+=$(OBJDIR)/rumpuser_daemonize.o $(OBJDIR)/rumpuser_dl.o

default:			$(LIB)

$(LIB):				$(OBJS)
				@mkdir -p $(LIBLIB)
				$(AR) cr $@ $(OBJS)

$(OBJDIR)/rumpuser.o:		rumpuser.c $(DEPS)
				@mkdir -p $(OBJDIR)
				$(COMPILE.c) -o $@ rumpuser.c

$(OBJDIR)/rumpuser_mem.o:	rumpuser_mem.c $(DEPS)
				@mkdir -p $(OBJDIR)
				$(COMPILE.c) -o $@ rumpuser_mem.c

$(OBJDIR)/rumpuser_random.o:	rumpuser_random.c $(DEPS)
				@mkdir -p $(OBJDIR)
				$(COMPILE.c) -o $@ rumpuser_random.c

$(OBJDIR)/rumpuser_component.o:	rumpuser_component.c $(DEPS)
				@mkdir -p $(OBJDIR)
				$(COMPILE.c) -o $@ rumpuser_component.c

$(OBJDIR)/rumpuser_sp.o:	rumpuser_sp.c $(DEPS)
				@mkdir -p $(OBJDIR)
				$(COMPILE.c) -o $@ rumpuser_sp.c

$(OBJDIR)/rumpuser_file.o:	rumpuser_file.c $(DEPS)
				@mkdir -p $(OBJDIR)
				$(COMPILE.c) -o $@ rumpuser_file.c

$(OBJDIR)/rumpuser_daemonize.o:	rumpuser_daemonize.c $(DEPS)
				@mkdir -p $(OBJDIR)
				$(COMPILE.c) -o $@ rumpuser_daemonize.c

$(OBJDIR)/rumpuser_dl.o:	rumpuser_dl.c $(DEPS)
				@mkdir -p $(OBJDIR)
				$(COMPILE.c) -o $@ rumpuser_dl.c

.PHONY:				clean
clean:				
				rm -f $(OBJS) $(LIB)
