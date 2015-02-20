ASRC=__clock_gettime.S clock_nanosleep.S _exit.S getrandom.S kill.S __mmap.S __munmap.S write.S
AOBJ=$(ASRC:.S=.o)
CSRC=clock_gettime.c getenv.c getpagesize.c mmap.c munmap.c __platform_init.c putchar.c raise.c
COBJ=$(CSRC:.c=.o)
OBJDIR=../../obj/libc
OBJ=$(addprefix $(OBJDIR)/,$(AOBJ) $(COBJ))
HEADERS=syscall.h syscall_nr.h
INCLUDES=-I../include
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-fno-stack-protector

default:			$(OBJDIR) $(OBJ)

$(OBJDIR):			
				mkdir -p $(OBJDIR)

$(OBJDIR)/clock_gettime.o:	clock_gettime.c $(HEADERS)
				$(COMPILE.c) -o $@ clock_gettime.c

$(OBJDIR)/__clock_gettime.o:	__clock_gettime.S $(HEADERS)
				$(COMPILE.S) -o $@ __clock_gettime.S

$(OBJDIR)/clock_nanosleep.o:	clock_nanosleep.S $(HEADERS)
				$(COMPILE.S) -o $@ clock_nanosleep.S

$(OBJDIR)/_exit.o:		_exit.S $(HEADERS)
				$(COMPILE.S) -o $@ _exit.S

$(OBJDIR)/getenv.o:		getenv.c $(HEADERS)
				$(COMPILE.c) -o $@ getenv.c

$(OBJDIR)/getpagesize.o:	getpagesize.c $(HEADERS)
				$(COMPILE.c) -o $@ getpagesize.c

$(OBJDIR)/getrandom.o:		getrandom.S $(HEADERS)
				$(COMPILE.S) -o $@ getrandom.S

$(OBJDIR)/kill.o:		kill.S $(HEADERS)
				$(COMPILE.S) -o $@ kill.S

$(OBJDIR)/__mmap.o:		__mmap.S $(HEADERS)
				$(COMPILE.S) -o $@ __mmap.S

$(OBJDIR)/mmap.o:		mmap.c $(HEADERS)
				$(COMPILE.c) -o $@ mmap.c

$(OBJDIR)/__munmap.o:		__munmap.S $(HEADERS)
				$(COMPILE.S) -o $@ __munmap.S

$(OBJDIR)/munmap.o:		munmap.c $(HEADERS)
				$(COMPILE.S) -o $@ munmap.c

$(OBJDIR)/__platform_init.o:	__platform_init.c $(HEADERS)
				$(COMPILE.c) -o $@ __platform_init.c

$(OBJDIR)/putchar.o:		putchar.c $(HEADERS)
				$(COMPILE.c) -o $@ putchar.c

$(OBJDIR)/raise.o:		raise.c $(HEADERS)
				$(COMPILE.c) -o $@ raise.c

$(OBJDIR)/write.o:		write.S $(HEADERS)
				$(COMPILE.S) -o $@ write.S

.PHONY:				clean
clean:		
				rm -f $(OBJ)
