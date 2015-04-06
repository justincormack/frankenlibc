COMPILE.c?=$(CC) -c $(CPPFLAGS) $(CFLAGS)
COMPILE.S?=$(CC) -c $(CPPFLAGS) $(ASFLAGS)
RUMPOBJ?=../../rumpobj
OBJDIR=$(RUMPOBJ)/libc
OBJ=$(OBJDIR)/fdinit.o
OBJ+=$(OBJDIR)/start_main.o
RUMP?=$(RUMPOBJ)/rump
INCLUDES=-I../include -I. -I$(RUMP)/include
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-fno-stack-protector
DEPS=$(OBJDIR)

default:			$(OBJ)

$(OBJDIR):			
				mkdir -p $(OBJDIR)

$(OBJDIR)/fdinit.o:		fdinit.c $(DEPS)
				$(COMPILE.c) -o $@ fdinit.c

$(OBJDIR)/start_main.o:		start_main.c $(DEPS)
				$(COMPILE.c) -o $@ start_main.c

.PHONY:				clean
clean:		
				rm -f $(OBJ)
