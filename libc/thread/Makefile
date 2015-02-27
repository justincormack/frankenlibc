OBJDIR=../../rumpobj/libc
OBJ=$(OBJDIR)/thread.o
HEADERS=thread.h
INCLUDES=-I../include
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-fno-stack-protector

default:		$(OBJ)

$(OBJDIR):	
			mkdir -p $(OBJDIR)

$(OBJDIR)/thread.o:	thread.c $(HEADERS) $(OBJDIR)
			$(COMPILE.c) -o $@ thread.c

.PHONY:			clean
clean:			
			rm -f $(OBJ)
