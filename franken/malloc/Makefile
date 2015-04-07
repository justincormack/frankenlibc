COMPILE.c?=$(CC) -c $(CPPFLAGS) $(CFLAGS)
COMPILE.S?=$(CC) -c $(CPPFLAGS) $(ASFLAGS)
RUMPOBJ?=../../rumpobj
OBJDIR=$(RUMPOBJ)/franken
OBJ+=$(OBJDIR)/malloc.o
INCLUDES=-I../include -I../../platform/include
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-fno-stack-protector
DEPS=$(OBJDIR)

default:			$(OBJ)

$(OBJDIR):			
				mkdir -p $(OBJDIR)

$(OBJDIR)/malloc.o:		malloc.c $(DEPS)
				$(COMPILE.c) -o $@ malloc.c

.PHONY:				clean
clean:		
				rm -f $(OBJ)
