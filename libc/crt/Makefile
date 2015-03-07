COMPILE.c?=$(CC) -c $(CPPFLAGS) $(CFLAGS)
COMPILE.S?=$(CC) -c $(CPPFLAGS) $(ASFLAGS)
OBJDIR=../../rump/lib
OBJ=$(OBJDIR)/crti.o $(OBJDIR)/crtn.o
OBJ+=$(OBJDIR)/crtbegin.o $(OBJDIR)/crtbeginT.o
OBJ+=$(OBJDIR)/crtend.o $(OBJDIR)/Scrt1.o
CPPFLAGS+=-nostdinc
CFLAGS+=-fno-stack-protector

default:		$(OBJDIR) $(OBJ)

$(OBJDIR):		
			mkdir -p $(OBJDIR)

$(OBJDIR)/crti.o:	crti.c
			$(COMPILE.c) -o $@ crti.c

$(OBJDIR)/crtn.o:	crtn.c
			$(COMPILE.c) -o $@ crtn.c

$(OBJDIR)/crtbegin.o:	crtbegin.c
			$(COMPILE.c) -o $@ crtbegin.c

$(OBJDIR)/crtbeginT.o:	crtbeginT.c
			$(COMPILE.c) -o $@ crtbeginT.c

$(OBJDIR)/crtend.o:	crtend.c
			$(COMPILE.c) -o $@ crtend.c

.PHONY:			clean
clean:			
			rm -f $(OBJ)
