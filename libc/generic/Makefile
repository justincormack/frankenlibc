ARCH=x86_64
ASRC=$(ARCH)/swapcontext.s
AOBJ=$(ASRC:.s=.o)
CSRC=$(ARCH)/context.c abort.c aligned_alloc.c assert.c calloc.c errno.c __libc_start_main.c malloc.c memcpy.c memset.c strcmp.c strcpy.c strdup.c strlen.c strncpy.c
COBJ=$(CSRC:.c=.o)
OBJ=$(AOBJ) $(COBJ)
INCLUDES=-I../../include
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-fno-stack-protector

default:		$(OBJ)

context.o:		$(ARCH)/context.c

swapcontext.o:		$(ARCH)/swapcontext.s

abort.o:		abort.c

aligned_alloc.o:	aligned_alloc.c

assert.o:		assert.c

calloc.o:		calloc.c

errno.o:		errno.c

__libc_start_main.o:	__libc_start_main.c

malloc.o:		malloc.c

memcpy.o:		memcpy.c

memset.o:		memset.c

strcmp.o:		strcmp.c

strcpy.o:		strcpy.c

strdup.o:		strdup.c

strlen.o:		strlen.c

strncpy.o:		strncpy.c

.PHONY:			clean
clean:		
			rm -f *.o */*.o
