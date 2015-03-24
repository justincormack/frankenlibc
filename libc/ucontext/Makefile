COMPILE.c?=$(CC) -c $(CPPFLAGS) $(CFLAGS)
COMPILE.S?=$(CC) -c $(CPPFLAGS) $(ASFLAGS)
OBJDIR=../../rumpobj/libc
OBJ=$(OBJDIR)/makecontext.o $(OBJDIR)/getcontext.o $(OBJDIR)/swapcontext.o
INCLUDES=-I../include -I.
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-fno-stack-protector

default:			$(OBJ)

$(OBJDIR):			
				mkdir -p $(OBJDIR)

$(OBJDIR)/getcontext.o:		getcontext.c $(OBJDIR)
				$(COMPILE.c) -o $@ getcontext.c

$(OBJDIR)/makecontext.o:	makecontext.c $(OBJDIR)
				$(COMPILE.c) -o $@ makecontext.c

$(OBJDIR)/swapcontext.o:	swapcontext.S $(OBJDIR)
				$(COMPILE.S) -o $@ swapcontext.S

.PHONY:				clean
clean:		
				rm -f $(OBJ)
