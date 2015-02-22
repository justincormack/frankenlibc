OBJDIR=../../obj/libc
OBJ=$(OBJDIR)/clock_gettime.o $(OBJDIR)/__clock_gettime.o $(OBJDIR)/clock_nanosleep.o $(OBJDIR)/_exit.o $(OBJDIR)/getpagesize.o $(OBJDIR)/getrandom.o $(OBJDIR)/ioctl.o $(OBJDIR)/isatty.o $(OBJDIR)/kill.o $(OBJDIR)/__mmap.o $(OBJDIR)/mmap.o $(OBJDIR)/__munmap.o $(OBJDIR)/munmap.o $(OBJDIR)/__platform_init.o $(OBJDIR)/write.o
HEADERS=syscall.h arm/syscall.h i386/syscall.h x86_64/syscall.h
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

$(OBJDIR)/getpagesize.o:	getpagesize.c $(HEADERS)
				$(COMPILE.c) -o $@ getpagesize.c

$(OBJDIR)/getrandom.o:		getrandom.S $(HEADERS)
				$(COMPILE.S) -o $@ getrandom.S

$(OBJDIR)/ioctl.o:		ioctl.S $(HEADERS)
				$(COMPILE.S) -o $@ ioctl.S

$(OBJDIR)/isatty.o:		isatty.c $(HEADERS)
				$(COMPILE.c) -o $@ isatty.c

$(OBJDIR)/kill.o:		kill.S $(HEADERS)
				$(COMPILE.S) -o $@ kill.S

$(OBJDIR)/__mmap.o:		__mmap.S $(HEADERS)
				$(COMPILE.S) -o $@ __mmap.S

$(OBJDIR)/mmap.o:		mmap.c $(HEADERS)
				$(COMPILE.c) -o $@ mmap.c

$(OBJDIR)/__munmap.o:		__munmap.S $(HEADERS)
				$(COMPILE.S) -o $@ __munmap.S

$(OBJDIR)/munmap.o:		munmap.c $(HEADERS)
				$(COMPILE.c) -o $@ munmap.c

$(OBJDIR)/__platform_init.o:	__platform_init.c $(HEADERS)
				$(COMPILE.c) -o $@ __platform_init.c

$(OBJDIR)/write.o:		write.S $(HEADERS)
				$(COMPILE.S) -o $@ write.S

.PHONY:				clean
clean:		
				rm -f $(OBJ)
