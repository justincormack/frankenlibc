COMPILE.c?=$(CC) -c $(CPPFLAGS) $(CFLAGS)
COMPILE.S?=$(CC) -c $(CPPFLAGS) $(ASFLAGS)
RUMPOBJ?=../../rumpobj
OBJDIR=$(RUMPOBJ)/franken
OBJ+=$(OBJDIR)/aligned_alloc.o
OBJ+=$(OBJDIR)/calloc.o
OBJ+=$(OBJDIR)/malloc.o
OBJ+=$(OBJDIR)/posix_memalign.o
INCLUDES=-I../include -I../../platform/include
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-fno-stack-protector
DEPS=$(OBJDIR)

default:			$(OBJ)

$(OBJDIR):			
				mkdir -p $(OBJDIR)

$(OBJDIR)/aligned_alloc.o:	aligned_alloc.c $(DEPS)
				$(COMPILE.c) -o $@ aligned_alloc.c

$(OBJDIR)/calloc.o:		calloc.c $(DEPS)
				$(COMPILE.c) -o $@ calloc.c

$(OBJDIR)/malloc.o:		malloc.c $(DEPS)
				$(COMPILE.c) -o $@ malloc.c

$(OBJDIR)/posix_memalign.o:	posix_memalign.c $(DEPS)
				$(COMPILE.c) -o $@ posix_memalign.c

.PHONY:				clean
clean:		
				rm -f $(OBJ)
