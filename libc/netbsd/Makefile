OBJDIR=../../obj/libc
CRTDIR=../../rump/lib
CRTOBJDIR=../../obj/crt
OBJ=$(CRTDIR)/crt0.o $(OBJDIR)/clock_gettime.o $(OBJDIR)/clock_nanosleep.o $(OBJDIR)/_exit.o $(OBJDIR)/getpagesize.o $(OBJDIR)/getrandom.o $(OBJDIR)/ioctl.o $(OBJDIR)/isatty.o $(OBJDIR)/kill.o $(OBJDIR)/mmap.o $(OBJDIR)/munmap.o $(OBJDIR)/sysctl.o $(OBJDIR)/write.o
HEADERS=syscall.h x86_64/syscall.h
INCLUDES=-I../include -I../crt
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-fno-stack-protector

default:			$(OBJDIR) $(CRTDIR) $(OBJCRTDIR) $(OBJ)

$(OBJDIR):			
				mkdir -p $(OBJDIR)

$(CRTDIR):			
				mkdir -p $(CRTDIR)

$(CRTOBJDIR):			
				mkdir -p $(CRTOBJDIR)

$(CRTDIR)/crt0.o:		$(CRTOBJDIR)/start.o $(CRTOBJDIR)/crt0.o $(CRTDIR)
				$(CC) $(LDFLAGS) -nostdlib -Wl,-r $(CRTOBJDIR)/start.o $(CRTOBJDIR)/crt0.o -o $@

$(CRTOBJDIR)/start.o:		start.s $(CRTOBJDIR)
				$(COMPILE.s) -o $@ start.s

$(CRTOBJDIR)/crt0.o:		crt0.c x86_64/crt0.c $(CRTOBJDIR)
				$(COMPILE.c) -o $@ crt0.c
	
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

$(OBJDIR)/ioctl.o:		ioctl.S $(HEADERS)
				$(COMPILE.S) -o $@ ioctl.S

$(OBJDIR)/isatty.o:		isatty.c $(HEADERS)
				$(COMPILE.c) -o $@ isatty.c

$(OBJDIR)/kill.o:		kill.S $(HEADERS)
				$(COMPILE.S) -o $@ kill.S

$(OBJDIR)/mmap.o:		mmap.S $(HEADERS)
				$(COMPILE.S) -o $@ mmap.S

$(OBJDIR)/munmap.o:		munmap.S $(HEADERS)
				$(COMPILE.S) -o $@ munmap.S

$(OBJDIR)/sysctl.o:		sysctl.S $(HEADERS)
				$(COMPILE.S) -o $@ sysctl.S

$(OBJDIR)/write.o:		write.S $(HEADERS)
				$(COMPILE.S) -o $@ write.S

.PHONY:				clean
clean:		
				rm -f $(OBJ)
