OBJDIR=../../obj/libc
OBJ=$(OBJDIR)/context.o $(OBJDIR)/swapcontext.o $(OBJDIR)/abort.o $(OBJDIR)/aligned_alloc.o $(OBJDIR)/assert.o $(OBJDIR)/calloc.o $(OBJDIR)/errno.o $(OBJDIR)/__errno.o $(OBJDIR)/getenv.o $(OBJDIR)/__libc_start_main.o $(OBJDIR)/malloc.o $(OBJDIR)/memcpy.o $(OBJDIR)/memset.o $(OBJDIR)/_mmap.o $(OBJDIR)/posix_memalign.o $(OBJDIR)/strchr.o $(OBJDIR)/strcmp.o $(OBJDIR)/strcpy.o $(OBJDIR)/strdup.o $(OBJDIR)/strlen.o $(OBJDIR)/strncmp.o $(OBJDIR)/strncpy.o
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

$(OBJDIR)/context.o:		context.c x86_64/context.c
				$(COMPILE.c) -o $@ context.c

$(OBJDIR)/errno.o:		errno.c
				$(COMPILE.c) -o $@ errno.c

$(OBJDIR)/__errno.o:		__errno.c
				$(COMPILE.c) -o $@ __errno.c

$(OBJDIR)/getenv.o:		getenv.c
				$(COMPILE.c) -o $@ getenv.c

$(OBJDIR)/__libc_start_main.o:	__libc_start_main.c
				$(COMPILE.c) $(RUMPINC) -o $@ __libc_start_main.c

$(OBJDIR)/malloc.o:		malloc.c
				$(COMPILE.c) -o $@ malloc.c

$(OBJDIR)/memcpy.o:		memcpy.c
				$(COMPILE.c) -o $@ memcpy.c

$(OBJDIR)/memset.o:		memset.c
				$(COMPILE.c) -o $@ memset.c

$(OBJDIR)/_mmap.o:		_mmap.c
				$(COMPILE.c) -o $@ _mmap.c

$(OBJDIR)/posix_memalign.o:	posix_memalign.c
				$(COMPILE.c) -o $@ posix_memalign.c

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
