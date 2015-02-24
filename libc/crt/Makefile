OBJDIR=../../rump/lib
OBJ=$(OBJDIR)/crti.o $(OBJDIR)/crtn.o
CPPFLAGS+=-nostdinc
CFLAGS+=-fno-stack-protector

default:		$(OBJDIR) $(OBJ)

$(OBJDIR):		
			mkdir -p $(OBJDIR)

$(OBJDIR)/crti.o:	crti.c
			$(COMPILE.c) -o $@ crti.c

$(OBJDIR)/crtn.o:	crtn.c
			$(COMPILE.c) -o $@ crtn.c

.PHONY:			clean
clean:			
			rm -f $(OBJ)
