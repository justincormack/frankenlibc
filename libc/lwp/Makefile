CSRC=_lwp_kill.c _lwp_self.c
COBJ=$(CSRC:.c=.o)
OBJDIR=../../obj/libc
OBJ=$(addprefix $(OBJDIR)/,$(COBJ))
INCLUDES=-I../include
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-fno-stack-protector

default:			$(OBJDIR) $(OBJ)

$(OBJDIR):			
				mkdir -p $(OBJDIR)

$(OBJDIR)/_lwp_kill.o:		_lwp_kill.c
				$(COMPILE.c) -o $@ _lwp_kill.c

$(OBJDIR)/_lwp_self.o:		_lwp_self.c
				$(COMPILE.c) -o $@ _lwp_self.c

.PHONY:				clean
clean:		
				rm -f $(OBJ)
