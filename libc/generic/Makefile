OBJDIR=../../rumpobj/libc
OBJ=$(OBJDIR)/makecontext.o $(OBJDIR)/getcontext.o $(OBJDIR)/swapcontext.o $(OBJDIR)/abort.o $(OBJDIR)/aligned_alloc.o $(OBJDIR)/assert.o $(OBJDIR)/calloc.o $(OBJDIR)/errno.o $(OBJDIR)/getenv.o $(OBJDIR)/malloc.o $(OBJDIR)/memcpy.o $(OBJDIR)/memset.o $(OBJDIR)/posix_memalign.o $(OBJDIR)/putchar.o $(OBJDIR)/raise.o $(OBJDIR)/strchr.o $(OBJDIR)/strcmp.o $(OBJDIR)/strcpy.o $(OBJDIR)/strdup.o $(OBJDIR)/strlen.o $(OBJDIR)/strncmp.o $(OBJDIR)/strncpy.o
INCLUDES=-I../include
RUMPINC=-I../../rump/include
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-fno-stack-protector

default:			$(OBJDIR) $(OBJ)

$(OBJDIR):			
				mkdir -p $(OBJDIR)

$(OBJDIR)/abort.o:		abort.c
				$(COMPILE.c) -o $@ abort.c

$(OBJDIR)/aligned_alloc.o:	aligned_alloc.c
				$(COMPILE.c) -o $@ aligned_alloc.c

$(OBJDIR)/assert.o:		assert.c
				$(COMPILE.c) -o $@ assert.c

$(OBJDIR)/calloc.o:		calloc.c
				$(COMPILE.c) -o $@ calloc.c

$(OBJDIR)/errno.o:		errno.c
				$(COMPILE.c) -o $@ errno.c

$(OBJDIR)/getcontext.o:		getcontext.c
				$(COMPILE.c) -o $@ getcontext.c

$(OBJDIR)/getenv.o:		getenv.c
				$(COMPILE.c) -o $@ getenv.c

$(OBJDIR)/makecontext.o:	makecontext.c x86_64/makecontext.c
				$(COMPILE.c) -o $@ makecontext.c

$(OBJDIR)/malloc.o:		malloc.c
				$(COMPILE.c) -o $@ malloc.c

$(OBJDIR)/memcpy.o:		memcpy.c
				$(COMPILE.c) -o $@ memcpy.c

$(OBJDIR)/memset.o:		memset.c
				$(COMPILE.c) -o $@ memset.c

$(OBJDIR)/posix_memalign.o:	posix_memalign.c
				$(COMPILE.c) -o $@ posix_memalign.c

$(OBJDIR)/putchar.o:		putchar.c
				$(COMPILE.c) -o $@ putchar.c

$(OBJDIR)/raise.o:		raise.c
				$(COMPILE.c) -o $@ raise.c

$(OBJDIR)/strchr.o:		strchr.c
				$(COMPILE.c) -o $@ strchr.c

$(OBJDIR)/strcmp.o:		strcmp.c
				$(COMPILE.c) -o $@ strcmp.c

$(OBJDIR)/strcpy.o:		strcpy.c
				$(COMPILE.c) -o $@ strcpy.c

$(OBJDIR)/strdup.o:		strdup.c
				$(COMPILE.c) -o $@ strdup.c

$(OBJDIR)/strlen.o:		strlen.c
				$(COMPILE.c) -o $@ strlen.c

$(OBJDIR)/strncmp.o:		strncmp.c
				$(COMPILE.c) -o $@ strncmp.c

$(OBJDIR)/strncpy.o:		strncpy.c
				$(COMPILE.c) -o $@ strncpy.c

$(OBJDIR)/swapcontext.o:	swapcontext.S x86_64/swapcontext.s
				$(COMPILE.S) -o $@ swapcontext.S

.PHONY:				clean
clean:		
				rm -f $(OBJ)
