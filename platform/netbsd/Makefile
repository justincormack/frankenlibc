COMPILE.c?=$(CC) -c $(CPPFLAGS) $(CFLAGS)
COMPILE.S?=$(CC) -c $(CPPFLAGS) $(ASFLAGS)
RUMPOBJ?=../../rumpobj
OBJDIR=$(RUMPOBJ)/platform
RUMP?=$(RUMPOBJ)/rump
CRTDIR=$(RUMP)/lib
OBJ=$(CRTDIR)/crt0.o
OBJ+=$(CRTDIR)/crti.o $(CRTDIR)/crtn.o
OBJ+=$(OBJDIR)/clock_getres.o $(OBJDIR)/clock_gettime.o
OBJ+=$(OBJDIR)/clock_nanosleep.o $(OBJDIR)/__clock_nanosleep.o
OBJ+=$(OBJDIR)/_exit.o $(OBJDIR)/fstat.o $(OBJDIR)/fsync.o
OBJ+=$(OBJDIR)/getpagesize.o $(OBJDIR)/getrandom.o
OBJ+=$(OBJDIR)/ioctl.o $(OBJDIR)/kill.o $(OBJDIR)/mmap.o
OBJ+=$(OBJDIR)/munmap.o $(OBJDIR)/mprotect.o $(OBJDIR)/nanosleep.o
OBJ+=$(OBJDIR)/pread.o $(OBJDIR)/pwrite.o $(OBJDIR)/read.o
OBJ+=$(OBJDIR)/___start.o
OBJ+=$(OBJDIR)/sysctl.o $(OBJDIR)/write.o
HEADERS=syscall.h i386/syscall.h x86_64/syscall.h netbsd.h
INCLUDES=-I../include -I../../franken/include -I.
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-fno-stack-protector

default:			$(OBJDIR) $(CRTDIR) $(OBJCRTDIR) $(OBJ)

$(OBJDIR):			
				mkdir -p $(OBJDIR)

$(CRTDIR):			
				mkdir -p $(CRTDIR)

$(CRTDIR)/crt0.o:		crt0.S x86_64/crt0.S i386/crt0.S $(CRTOBJDIR)
				$(COMPILE.S) -o $@ crt0.S

$(CRTDIR)/crti.o:		crti.S
				$(COMPILE.S) -o $@ crti.S

$(CRTDIR)/crtn.o:		crtn.S
				$(COMPILE.S) -o $@ crtn.S

$(OBJDIR)/clock_getres.o:	clock_getres.S $(HEADERS)
				$(COMPILE.S) -o $@ clock_getres.S

$(OBJDIR)/clock_gettime.o:	clock_gettime.S $(HEADERS)
				$(COMPILE.S) -o $@ clock_gettime.S

$(OBJDIR)/clock_nanosleep.o:	clock_nanosleep.c $(HEADERS)
				$(COMPILE.c) -o $@ clock_nanosleep.c

$(OBJDIR)/__clock_nanosleep.o:	__clock_nanosleep.S $(HEADERS)
				$(COMPILE.S) -o $@ __clock_nanosleep.S

$(OBJDIR)/_exit.o:		_exit.S $(HEADERS)
				$(COMPILE.S) -o $@ _exit.S

$(OBJDIR)/fstat.o:		fstat.S $(HEADERS)
				$(COMPILE.S) -o $@ fstat.S

$(OBJDIR)/fsync.o:		fsync.S $(HEADERS)
				$(COMPILE.S) -o $@ fsync.S

$(OBJDIR)/getpagesize.o:	getpagesize.c $(HEADERS)
				$(COMPILE.c) -o $@ getpagesize.c

$(OBJDIR)/getrandom.o:		getrandom.c $(HEADERS)
				$(COMPILE.c) -o $@ getrandom.c

$(OBJDIR)/ioctl.o:		ioctl.S $(HEADERS)
				$(COMPILE.S) -o $@ ioctl.S

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

$(OBJDIR)/pread.o:		pread.S $(HEADERS)
				$(COMPILE.S) -o $@ pread.S

$(OBJDIR)/pwrite.o:		pwrite.S $(HEADERS)
				$(COMPILE.S) -o $@ pwrite.S

$(OBJDIR)/read.o:		read.S $(HEADERS)
				$(COMPILE.S) -o $@ read.S

$(OBJDIR)/___start.o:		___start.c $(HEADERS)
				$(COMPILE.c) -o $@ ___start.c

$(OBJDIR)/sysctl.o:		sysctl.S $(HEADERS)
				$(COMPILE.S) -o $@ sysctl.S

$(OBJDIR)/write.o:		write.S $(HEADERS)
				$(COMPILE.S) -o $@ write.S

.PHONY:				clean
clean:		
				rm -f rm -f $(OBJDIR)/*.o $(CRTDIR)/*.o
