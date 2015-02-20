ARCH=x86_64
ASRC=swapcontext.s
AOBJ=$(ASRC:.s=.o)
CSRC=abort.c aligned_alloc.c assert.c calloc.c context.c errno.c __errno.c __libc_start_main.c malloc.c memcpy.c memset.c strcmp.c strcpy.c strdup.c strlen.c strncpy.c
COBJ=$(CSRC:.c=.o)
OBJDIR=../../obj/libc
OBJ=$(addprefix $(OBJDIR)/,$(AOBJ) $(COBJ))
INCLUDES=-I../include
RUMPINC=-I../../rump/include
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-fno-stack-protector

default:			$(OBJDIR) $(OBJ)

$(OBJDIR):			
				mkdir -p $(OBJDIR)

$(OBJDIR)/context.o:		$(ARCH)/context.c
				$(COMPILE.c) -o $@ $(ARCH)/context.c

$(OBJDIR)/swapcontext.o:	$(ARCH)/swapcontext.s
				$(COMPILE.s) -o $@ $(ARCH)/swapcontext.s

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

$(OBJDIR)/__errno.o:		__errno.c
				$(COMPILE.c) -o $@ __errno.c

$(OBJDIR)/__libc_start_main.o:	__libc_start_main.c
				$(COMPILE.c) $(RUMPINC) -o $@ __libc_start_main.c

$(OBJDIR)/malloc.o:		malloc.c
				$(COMPILE.c) -o $@ malloc.c

$(OBJDIR)/memcpy.o:		memcpy.c
				$(COMPILE.c) -o $@ memcpy.c

$(OBJDIR)/memset.o:		memset.c
				$(COMPILE.c) -o $@ memset.c

$(OBJDIR)/strcmp.o:		strcmp.c
				$(COMPILE.c) -o $@ strcmp.c

$(OBJDIR)/strcpy.o:		strcpy.c
				$(COMPILE.c) -o $@ strcpy.c

$(OBJDIR)/strdup.o:		strdup.c
				$(COMPILE.c) -o $@ strdup.c

$(OBJDIR)/strlen.o:		strlen.c
				$(COMPILE.c) -o $@ strlen.c

$(OBJDIR)/strncpy.o:		strncpy.c
				$(COMPILE.c) -o $@ strncpy.c

.PHONY:				clean
clean:		
				rm -f $(OBJ)
