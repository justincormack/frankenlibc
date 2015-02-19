ASRC=__clock_gettime.S clock_nanosleep.S exit.S getrandom.S kill.S __mmap.S munmap.S write.S
AOBJ=$(ASRC:.S=.o)
CSRC=clock_gettime.c getenv.c getpagesize.c mmap.c __platform_init.c putchar.c raise.c
COBJ=$(CSRC:.c=.o)
OBJ=$(AOBJ) $(COBJ)
HEADERS=syscall.h syscall_nr.h
INCLUDES=-I../../include
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-fno-stack-protector

default:		$(OBJ)

clock_gettime.o:	clock_gettime.c $(HEADERS)

__clock_gettime.o:	__clock_gettime.S $(HEADERS)

clock_nanosleep.o:	clock_nanosleep.S $(HEADERS)

exit.o:			exit.S $(HEADERS)

getenv.o:		getenv.c $(HEADERS)

getpagesize.o:		getpagesize.c $(HEADERS)

getrandom.o:		getrandom.S $(HEADERS)

kill.o:			kill.S $(HEADERS)

__mmap.o:		__mmap.S $(HEADERS)

mmap.o:			mmap.c $(HEADERS)

munmap.o:		munmap.S $(HEADERS)

__platform_init.o:	__platform_init.c $(HEADERS)

putchar.o:		putchar.c $(HEADERS)

raise.o:		raise.c $(HEADERS)

write.o:		write.S $(HEADERS)

.PHONY:			clean
clean:		
			rm -f *.o
