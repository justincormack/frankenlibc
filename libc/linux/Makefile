COMPILE.c?=$(CC) -c $(CPPFLAGS) $(CFLAGS)
COMPILE.S?=$(CC) -c $(CPPFLAGS) $(ASFLAGS)
OBJDIR=../../rumpobj/libc
CRTDIR=../../rump/lib
OBJ=$(CRTDIR)/crt1.o $(CRTDIR)/Scrt1.o
OBJ+=$(OBJDIR)/arch_prctl.o
OBJ+=$(OBJDIR)/clock_getres.o $(OBJDIR)/__clock_getres.o
OBJ+=$(OBJDIR)/clock_gettime.o $(OBJDIR)/__clock_gettime.o
OBJ+=$(OBJDIR)/clock_nanosleep.o $(OBJDIR)/__clock_nanosleep.o
OBJ+=$(OBJDIR)/_exit.o $(OBJDIR)/fstat.o $(OBJDIR)/__fstat.o
OBJ+=$(OBJDIR)/fsync.o $(OBJDIR)/getpagesize.o
OBJ+=$(OBJDIR)/getrandom.o $(OBJDIR)/__getrandom.o
OBJ+=$(OBJDIR)/ioctl.o $(OBJDIR)/isatty.o $(OBJDIR)/kill.o
OBJ+=$(OBJDIR)/__mmap.o $(OBJDIR)/mmap.o
OBJ+=$(OBJDIR)/__mprotect.o $(OBJDIR)/mprotect.o
OBJ+=$(OBJDIR)/__munmap.o $(OBJDIR)/munmap.o
OBJ+=$(OBJDIR)/__platform_init.o
OBJ+=$(OBJDIR)/pread.o $(OBJDIR)/__pread.o
OBJ+=$(OBJDIR)/pwrite.o $(OBJDIR)/__pwrite.o
OBJ+=$(OBJDIR)/read.o
OBJ+=$(OBJDIR)/set_thread_area.o $(OBJDIR)/write.o
HEADERS=syscall.h arm/syscall.h i386/syscall.h x86_64/syscall.h
HEADERS+=linux.h i386/linux.h x86_64/linux.h
INCLUDES=-I../include
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-fno-stack-protector

default:			$(CRTDIR) $(OBJDIR) $(OBJ)

$(OBJDIR):			
				mkdir -p $(OBJDIR)

$(CRTDIR):			
				mkdir -p $(CRTDIR)

$(CRTDIR)/crt1.o:		crt1.c arm/crt1.c i386/crt1.c x86_64/crt1.c ../crt/__libc_start_main.c
				$(COMPILE.c) -o $@ crt1.c

$(CRTDIR)/Scrt1.o:		$(CRTDIR)/crt1.o
				ln $(CRTDIR)/crt1.o $@

$(OBJDIR)/arch_prctl.o:		arch_prctl.S $(HEADERS)
				$(COMPILE.S) -o $@ arch_prctl.S

$(OBJDIR)/clock_getres.o:	clock_getres.c $(HEADERS)
				$(COMPILE.c) -o $@ clock_getres.c

$(OBJDIR)/__clock_getres.o:	__clock_getres.S $(HEADERS)
				$(COMPILE.S) -o $@ __clock_getres.S

$(OBJDIR)/clock_gettime.o:	clock_gettime.c $(HEADERS)
				$(COMPILE.c) -o $@ clock_gettime.c

$(OBJDIR)/__clock_gettime.o:	__clock_gettime.S $(HEADERS)
				$(COMPILE.S) -o $@ __clock_gettime.S

$(OBJDIR)/clock_nanosleep.o:	clock_nanosleep.c $(HEADERS)
				$(COMPILE.c) -o $@ clock_nanosleep.c

$(OBJDIR)/__clock_nanosleep.o:	__clock_nanosleep.S $(HEADERS)
				$(COMPILE.S) -o $@ __clock_nanosleep.S

$(OBJDIR)/_exit.o:		_exit.S $(HEADERS)
				$(COMPILE.S) -o $@ _exit.S

$(OBJDIR)/fstat.o:		fstat.c $(HEADERS)
				$(COMPILE.c) -o $@ fstat.c

$(OBJDIR)/__fstat.o:		__fstat.S $(HEADERS)
				$(COMPILE.S) -o $@ __fstat.S

$(OBJDIR)/fsync.o:		fsync.S $(HEADERS)
				$(COMPILE.S) -o $@ fsync.S

$(OBJDIR)/getpagesize.o:	getpagesize.c $(HEADERS)
				$(COMPILE.c) -o $@ getpagesize.c

$(OBJDIR)/getrandom.o:		getrandom.c $(HEADERS)
				$(COMPILE.c) -o $@ getrandom.c

$(OBJDIR)/__getrandom.o:	__getrandom.S $(HEADERS)
				$(COMPILE.S) -o $@ __getrandom.S

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

$(OBJDIR)/__mprotect.o:		__mprotect.S
				$(COMPILE.S) -o $@ __mprotect.S

$(OBJDIR)/mprotect.o:		mprotect.c
				$(COMPILE.c) -o $@ mprotect.c

$(OBJDIR)/__munmap.o:		__munmap.S $(HEADERS)
				$(COMPILE.S) -o $@ __munmap.S

$(OBJDIR)/munmap.o:		munmap.c $(HEADERS)
				$(COMPILE.c) -o $@ munmap.c

$(OBJDIR)/__platform_init.o:	__platform_init.c $(HEADERS)
				$(COMPILE.c) -o $@ __platform_init.c

$(OBJDIR)/pread.o:		pread.c $(HEADERS)
				$(COMPILE.c) -o $@ pread.c

$(OBJDIR)/__pread.o:		__pread.S $(HEADERS)
				$(COMPILE.S) -o $@ __pread.S

$(OBJDIR)/pwrite.o:		pwrite.c $(HEADERS)
				$(COMPILE.c) -o $@ pwrite.c

$(OBJDIR)/__pwrite.o:		__pwrite.S $(HEADERS)
				$(COMPILE.S) -o $@ __pwrite.S

$(OBJDIR)/read.o:		read.S $(HEADERS)
				$(COMPILE.S) -o $@ read.S

$(OBJDIR)/set_thread_area.o:	set_thread_area.c $(HEADERS)
				$(COMPILE.c) -o $@ set_thread_area.c

$(OBJDIR)/write.o:		write.S $(HEADERS)
				$(COMPILE.S) -o $@ write.S

.PHONY:				clean
clean:		
				rm -f $(OBJDIR)/*.o $(CRTDIR)/*.o
