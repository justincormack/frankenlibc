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

$(OBJDIR)/makecontext.o:	makecontext.c arm/makecontext.c i386/makecontext.c x86_64/makecontext.c $(OBJDIR)
				$(COMPILE.c) -o $@ makecontext.c

$(OBJDIR)/swapcontext.o:	swapcontext.S arm/swapcontext.S i386/swapcontext.S x86_64/swapcontext.S $(OBJDIR)
				$(COMPILE.S) -o $@ swapcontext.S

.PHONY:				clean
clean:		
				rm -f $(OBJ)
