OS=linux
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

$(OBJDIR)/crt1.o:	$(OS)/$(ARCH)/crt1.s
			$(COMPILE.s) -o $@ $(OS)/$(ARCH)/crt1.s

.PHONY:			clean
clean:		
			rm -f $(OBJ)
