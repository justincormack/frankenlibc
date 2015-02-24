OS?=linux
OBJDIR=../../rump/lib
OBJ=$(OBJDIR)/crti.o $(OBJDIR)/crtn.o $(OBJDIR)/crt1.o
INCLUDES=-I../include -I.
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-fno-stack-protector

default:		$(OBJDIR) $(OBJ)

$(OBJDIR):		
			mkdir -p $(OBJDIR)

$(OBJDIR)/crti.o:	crti.c
			$(COMPILE.c) -o $@ crti.c

$(OBJDIR)/crtn.o:	crtn.c
			$(COMPILE.c) -o $@ crtn.c

$(OBJDIR)/crt1.o:	__libc_start_main.c $(OS)/crt1.c $(OS)/x86_64/crt1.c 
			$(COMPILE.c) -o $@ $(OS)/crt1.c

.PHONY:			clean
clean:		
			rm -f $(OBJ)
