COMPILE.c?=$(CC) -c $(CPPFLAGS) $(CFLAGS)
COMPILE.S?=$(CC) -c $(CPPFLAGS) $(ASFLAGS)
RUMPOBJ?=../../rumpobj
OBJDIR=$(RUMPOBJ)/franken
OBJ=$(OBJDIR)/_lwp_exit.o $(OBJDIR)/_lwp_kill.o $(OBJDIR)/___lwp_park60.o $(OBJDIR)/_lwp_self.o $(OBJDIR)/__libc_static_tls_setup.o
INCLUDES=-I../include -I../../platform/include -I.
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-fno-stack-protector

default:			$(OBJ)

$(OBJDIR)/__libc_static_tls_setup.o:	__libc_static_tls_setup.c
					@mkdir -p $(OBJDIR)
					$(COMPILE.c) -o $@ __libc_static_tls_setup.c

$(OBJDIR)/_lwp_exit.o:		_lwp_exit.c
				@mkdir -p $(OBJDIR)
				$(COMPILE.c) -o $@ _lwp_exit.c

$(OBJDIR)/_lwp_kill.o:		_lwp_kill.c
				@mkdir -p $(OBJDIR)
				$(COMPILE.c) -o $@ _lwp_kill.c

$(OBJDIR)/___lwp_park60.o:	___lwp_park60.c
				@mkdir -p $(OBJDIR)
				$(COMPILE.c) -o $@ ___lwp_park60.c

$(OBJDIR)/_lwp_self.o:		_lwp_self.c
				@mkdir -p $(OBJDIR)
				$(COMPILE.c) -o $@ _lwp_self.c

.PHONY:				clean
clean:		
				rm -f $(OBJ)
