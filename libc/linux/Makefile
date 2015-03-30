COMPILE.c?=$(CC) -c $(CPPFLAGS) $(CFLAGS)
COMPILE.S?=$(CC) -c $(CPPFLAGS) $(ASFLAGS)
RUMPOBJ?=../../rumpobj
OBJDIR=$(RUMPOBJ)/libc
RUMP?=../../rump
CRTDIR=$(RUMP)/lib
OBJ=$(CRTDIR)/crt1.o $(CRTDIR)/Scrt1.o
OBJ+=$(OBJDIR)/clock_getres.o
OBJ+=$(OBJDIR)/clock_gettime.o
OBJ+=$(OBJDIR)/clock_nanosleep.o
OBJ+=$(OBJDIR)/_exit.o $(OBJDIR)/fstat.o
OBJ+=$(OBJDIR)/fsync.o $(OBJDIR)/getpagesize.o
OBJ+=$(OBJDIR)/getrandom.o
OBJ+=$(OBJDIR)/isatty.o $(OBJDIR)/kill.o
OBJ+=$(OBJDIR)/mmap.o
OBJ+=$(OBJDIR)/mprotect.o
OBJ+=$(OBJDIR)/munmap.o
OBJ+=$(OBJDIR)/__libc_start_main.o
OBJ+=$(OBJDIR)/pread.o
OBJ+=$(OBJDIR)/pwrite.o
OBJ+=$(OBJDIR)/read.o
OBJ+=$(OBJDIR)/set_thread_area.o $(OBJDIR)/write.o
OBJ+=$(OBJDIR)/syscall.o $(OBJDIR)/syscall_ret.o
OBJ+=$(OBJDIR)/vdso.o
HEADERS=syscall.h linux.h
INCLUDES=-I../include -I.
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-fno-stack-protector

default:			$(CRTDIR) $(OBJDIR) $(OBJ)

$(OBJDIR):			
				mkdir -p $(OBJDIR)

$(CRTDIR):			
				mkdir -p $(CRTDIR)

$(CRTDIR)/crt1.o:		crt1.S
				$(COMPILE.S) -o $@ crt1.S

$(CRTDIR)/Scrt1.o:		$(CRTDIR)/crt1.o
				ln -f $(CRTDIR)/crt1.o $@

$(OBJDIR)/clock_getres.o:	clock_getres.c $(HEADERS)
				$(COMPILE.c) -o $@ clock_getres.c

$(OBJDIR)/clock_gettime.o:	clock_gettime.c $(HEADERS)
				$(COMPILE.c) -o $@ clock_gettime.c

$(OBJDIR)/clock_nanosleep.o:	clock_nanosleep.c $(HEADERS)
				$(COMPILE.c) -o $@ clock_nanosleep.c

$(OBJDIR)/_exit.o:		_exit.c $(HEADERS)
				$(COMPILE.c) -o $@ _exit.c

$(OBJDIR)/fstat.o:		fstat.c $(HEADERS)
				$(COMPILE.c) -o $@ fstat.c

$(OBJDIR)/fsync.o:		fsync.c $(HEADERS)
				$(COMPILE.c) -o $@ fsync.c

$(OBJDIR)/getpagesize.o:	getpagesize.c $(HEADERS)
				$(COMPILE.c) -o $@ getpagesize.c

$(OBJDIR)/getrandom.o:		getrandom.c $(HEADERS)
				$(COMPILE.c) -o $@ getrandom.c

$(OBJDIR)/isatty.o:		isatty.c $(HEADERS)
				$(COMPILE.c) -o $@ isatty.c

$(OBJDIR)/kill.o:		kill.c $(HEADERS)
				$(COMPILE.c) -o $@ kill.c

$(OBJDIR)/__libc_start_main.o:	__libc_start_main.c $(HEADERS)
				$(COMPILE.c) -o $@ __libc_start_main.c

$(OBJDIR)/mmap.o:		mmap.c $(HEADERS)
				$(COMPILE.c) -o $@ mmap.c

$(OBJDIR)/mprotect.o:		mprotect.c
				$(COMPILE.c) -o $@ mprotect.c

$(OBJDIR)/munmap.o:		munmap.c $(HEADERS)
				$(COMPILE.c) -o $@ munmap.c

$(OBJDIR)/pread.o:		pread.c $(HEADERS)
				$(COMPILE.c) -o $@ pread.c

$(OBJDIR)/pwrite.o:		pwrite.c $(HEADERS)
				$(COMPILE.c) -o $@ pwrite.c

$(OBJDIR)/read.o:		read.c $(HEADERS)
				$(COMPILE.c) -o $@ read.c

$(OBJDIR)/set_thread_area.o:	set_thread_area.c $(HEADERS)
				$(COMPILE.c) -o $@ set_thread_area.c

$(OBJDIR)/syscall.o:		syscall.S $(HEADERS)
				$(COMPILE.S) -o $@ syscall.S

$(OBJDIR)/syscall_ret.o:	syscall_ret.c $(HEADERS)
				$(COMPILE.c) -o $@ syscall_ret.c

$(OBJDIR)/vdso.o:		vdso.c $(HEADERS)
				$(COMPILE.c) -o $@ vdso.c

$(OBJDIR)/write.o:		write.c $(HEADERS)
				$(COMPILE.c) -o $@ write.c

.PHONY:				clean
clean:		
				rm -f $(OBJDIR)/*.o $(CRTDIR)/*.o
