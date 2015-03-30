COMPILE.c?=$(CC) -c $(CPPFLAGS) $(CFLAGS)
COMPILE.S?=$(CC) -c $(CPPFLAGS) $(ASFLAGS)
RUMPOBJ?=../../rumpobj
OBJDIR=$(RUMPOBJ)/libc
OBJ=$(OBJDIR)/fdinit.o
RUMP?=$(RUMPOBJ)/rump
INCLUDES=-I../include -I. -I$(RUMP)/include
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-fno-stack-protector

default:			$(OBJDIR) $(OBJ)

$(OBJDIR):			
				mkdir -p $(OBJDIR)

$(OBJDIR)/fdinit.o:		fdinit.c
				$(COMPILE.c) -o $@ fdinit.c

.PHONY:				clean
clean:		
				rm -f $(OBJ)
