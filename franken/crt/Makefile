COMPILE.c?=$(CC) -c $(CPPFLAGS) $(CFLAGS)
COMPILE.S?=$(CC) -c $(CPPFLAGS) $(ASFLAGS)
RUMPOBJ?=../../rumpobj
RUMP?=$(RUMPOBJ)/rump
OBJDIR=$(RUMP)/lib
OBJ+=$(OBJDIR)/crtbegin.o $(OBJDIR)/crtbeginT.o
OBJ+=$(OBJDIR)/crtend.o
CPPFLAGS+=-nostdinc
CFLAGS+=-fno-stack-protector

default:		$(OBJDIR) $(OBJ)

$(OBJDIR):		
			mkdir -p $(OBJDIR)

$(OBJDIR)/crtbegin.o:	crtbegin.c
			$(COMPILE.c) -o $@ crtbegin.c

$(OBJDIR)/crtbeginT.o:	crtbeginT.c
			$(COMPILE.c) -o $@ crtbeginT.c

$(OBJDIR)/crtend.o:	crtend.c
			$(COMPILE.c) -o $@ crtend.c

.PHONY:			clean
clean:			
			rm -f $(OBJ)
