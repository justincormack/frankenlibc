OBJDIR=../../rumpobj/libc
CRTDIR=../../rump/lib
CRTOBJDIR=../../rumpobj/crt
OBJ=$(CRTDIR)/crt0.o
OBJ+=$(OBJDIR)/clock_gettime.o $(OBJDIR)/clock_nanosleep.o
OBJ+=$(OBJDIR)/__clock_nanosleep.o
OBJ+=$(OBJDIR)/_exit.o $(OBJDIR)/getpagesize.o $(OBJDIR)/getrandom.o
OBJ+=$(OBJDIR)/ioctl.o $(OBJDIR)/isatty.o $(OBJDIR)/kill.o $(OBJDIR)/mmap.o
OBJ+=$(OBJDIR)/munmap.o $(OBJDIR)/mprotect.o $(OBJDIR)/nanosleep.o
OBJ+=$(OBJDIR)/__platform_init.o
OBJ+=$(OBJDIR)/sysctl.o $(OBJDIR)/write.o
HEADERS=syscall.h x86_64/syscall.h
INCLUDES=-I../include
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
				$(CC) $(CFLAGS) -nostdlib -Wl,-r $(CRTOBJDIR)/start.o $(CRTOBJDIR)/crt0.o -o $@

$(CRTOBJDIR)/start.o:		start.S $(CRTOBJDIR)
				$(COMPILE.S) -o $@ start.S

$(CRTOBJDIR)/crt0.o:		crt0.c x86_64/crt0.c i386/crt0.c $(CRTOBJDIR) ../crt/__libc_start_main.c
				$(COMPILE.c) -o $@ crt0.c

$(CRTDIR)/crtbegin.o:		crtbegin.c
				$(COMPILE.c) -o $@ crtbegin.c
	
$(OBJDIR)/clock_gettime.o:	clock_gettime.S $(HEADERS)
				$(COMPILE.S) -o $@ clock_gettime.S

$(OBJDIR)/clock_nanosleep.o:	clock_nanosleep.c $(HEADERS)
				$(COMPILE.c) -o $@ clock_nanosleep.c

$(OBJDIR)/__clock_nanosleep.o:	__clock_nanosleep.S $(HEADERS)
				$(COMPILE.S) -o $@ __clock_nanosleep.S

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

$(OBJDIR)/mprotect.o:		mprotect.S $(HEADERS)
				$(COMPILE.S) -o $@ mprotect.S

$(OBJDIR)/munmap.o:		munmap.S $(HEADERS)
				$(COMPILE.S) -o $@ munmap.S

$(OBJDIR)/nanosleep.o:		nanosleep.S $(HEADERS)
				$(COMPILE.S) -o $@ nanosleep.S

$(OBJDIR)/__platform_init.o:	__platform_init.c
				$(COMPILE.c) -o $@ __platform_init.c

$(OBJDIR)/sysctl.o:		sysctl.S $(HEADERS)
				$(COMPILE.S) -o $@ sysctl.S

$(OBJDIR)/write.o:		write.S $(HEADERS)
				$(COMPILE.S) -o $@ write.S

.PHONY:				clean
clean:		
				rm -f $(OBJ) $(CRTOBJDIR)/start.o $(CRTOBJDIR)/crt0.o
