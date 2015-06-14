COMPILE.c?=$(CC) -c $(CPPFLAGS) $(CFLAGS)
COMPILE.S?=$(CC) -c $(CPPFLAGS) $(ASFLAGS)
RUMPOBJ?=../../rumpobj
OBJDIR=$(RUMPOBJ)/franken
OBJ=$(OBJDIR)/fdinit.o
OBJ+=$(OBJDIR)/start_main.o
RUMP?=$(RUMPOBJ)/rump
INCLUDES=-I../include -I../../platform/include -I. -I$(RUMP)/include
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-fno-stack-protector
DEPS=init.h

default:			$(OBJ)

$(OBJDIR)/fdinit.o:		fdinit.c $(DEPS)
				@mkdir -p $(OBJDIR)
				$(COMPILE.c) -o $@ fdinit.c

$(OBJDIR)/start_main.o:		start_main.c $(DEPS)
				@mkdir -p $(OBJDIR)
				$(COMPILE.c) -o $@ start_main.c

.PHONY:				clean
clean:		
				rm -f $(OBJ)
