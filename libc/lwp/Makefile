OBJDIR=../../obj/libc
OBJ=$(OBJDIR)/_lwp_kill.o $(OBJDIR)/_lwp_self.o $(OBJDIR)/__libc_static_tls_setup.o
INCLUDES=-I../include
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-fno-stack-protector

default:			$(OBJDIR) $(OBJ)

$(OBJDIR):			
				mkdir -p $(OBJDIR)

$(OBJDIR)/__libc_static_tls_setup.o:	__libc_static_tls_setup.c
					$(COMPILE.c) -o $@ __libc_static_tls_setup.c

$(OBJDIR)/_lwp_kill.o:		_lwp_kill.c
				$(COMPILE.c) -o $@ _lwp_kill.c

$(OBJDIR)/_lwp_self.o:		_lwp_self.c
				$(COMPILE.c) -o $@ _lwp_self.c

.PHONY:				clean
clean:		
				rm -f $(OBJ)
