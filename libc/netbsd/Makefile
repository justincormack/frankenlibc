OBJDIR=../../obj/libc
OBJ=$(OBJDIR)/clock_gettime.o $(OBJDIR)/clock_nanosleep.o $(OBJDIR)/_exit.o $(OBJDIR)/getpagesize.o $(OBJDIR)/getrandom.o $(OBJDIR)/kill.o $(OBJDIR)/mmap.o $(OBJDIR)/munmap.o $(OBJDIR)/raise.o $(OBJDIR)/start.o $(OBJDIR)/__sysctl.o $(OBJDIR)/write.o
HEADERS=syscall.h x86_64/syscall.h
INCLUDES=-I../include
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-fno-stack-protector

default:			$(OBJDIR) $(OBJ)

$(OBJDIR):			
				mkdir -p $(OBJDIR)

$(OBJDIR)/clock_gettime.o:	clock_gettime.S $(HEADERS)
				$(COMPILE.S) -o $@ clock_gettime.S

$(OBJDIR)/clock_nanosleep.o:	clock_nanosleep.S $(HEADERS)
				$(COMPILE.S) -o $@ clock_nanosleep.S

$(OBJDIR)/_exit.o:		_exit.S $(HEADERS)
				$(COMPILE.S) -o $@ _exit.S

$(OBJDIR)/getpagesize.o:	getpagesize.c $(HEADERS)
				$(COMPILE.c) -o $@ getpagesize.c

$(OBJDIR)/getrandom.o:		getrandom.c $(HEADERS)
				$(COMPILE.c) -o $@ getrandom.c

$(OBJDIR)/kill.o:		kill.S $(HEADERS)
				$(COMPILE.S) -o $@ kill.S

$(OBJDIR)/mmap.o:		mmap.S $(HEADERS)
				$(COMPILE.S) -o $@ mmap.S

$(OBJDIR)/munmap.o:		munmap.S $(HEADERS)
				$(COMPILE.S) -o $@ munmap.S

$(OBJDIR)/raise.o:		raise.c $(HEADERS)
				$(COMPILE.c) -o $@ raise.c

$(OBJDIR)/start.o:		start.s $(HEADERS)
				$(COMPILE.s) -o $@ start.s

$(OBJDIR)/__sysctl.o:		__sysctl.S $(HEADERS)
				$(COMPILE.S) -o $@ __sysctl.S

$(OBJDIR)/write.o:		write.S $(HEADERS)
				$(COMPILE.S) -o $@ write.S

.PHONY:				clean
clean:		
				rm -f $(OBJ)
