OS?=linux
OBJDIR=../../lib
OBJ=$(OBJDIR)/crti.o $(OBJDIR)/crtn.o $(OBJDIR)/crt1.o
CPPFLAGS+=-nostdinc
CFLAGS+=-fno-stack-protector

default:		$(OBJDIR) $(OBJ)

$(OBJDIR):		
			mkdir -p $(OBJDIR)

$(OBJDIR)/crti.o:	crti.c
			$(COMPILE.c) -o $@ crti.c

$(OBJDIR)/crtn.o:	crtn.c
			$(COMPILE.c) -o $@ crtn.c

$(OBJDIR)/crt1.o:	$(OS)/crt1.S $(OS)/crt1.S $(OS)/x86_64/crt1.s 
			$(COMPILE.S) -o $@ $(OS)/crt1.S

.PHONY:			clean
clean:		
			rm -f $(OBJ)
