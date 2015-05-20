COMPILE.c?=$(CC) -c $(CPPFLAGS) $(CFLAGS)
COMPILE.S?=$(CC) -c $(CPPFLAGS) $(ASFLAGS)
RUMPOBJ?=../../rumpobj
OBJDIR=$(RUMPOBJ)/platform
RUMP?=$(RUMPOBJ)/rump
CRTDIR=$(RUMP)/lib
CRTFILES=$(CRTDIR)/crt0.o $(CRTDIR)/crt.o
CRTFILES+=$(CRTDIR)/crti.o $(CRTDIR)/crtn.o
CRTFILES+=$(CRTDIR)/crtbegin.o $(CRTDIR)/crtbeginT.o
CRTFILES+=$(CRTDIR)/crtend.o
OBJ=$(CRTFILES)
OBJ+=$(OBJDIR)/clock_getres.o
OBJ+=$(OBJDIR)/clock_gettime.o
OBJ+=$(OBJDIR)/clock_nanosleep.o
OBJ+=$(OBJDIR)/_exit.o
OBJ+=$(OBJDIR)/fcntl.o
OBJ+=$(OBJDIR)/fstat.o
OBJ+=$(OBJDIR)/fsync.o
OBJ+=$(OBJDIR)/getpagesize.o
OBJ+=$(OBJDIR)/getrandom.o
OBJ+=$(OBJDIR)/kill.o
OBJ+=$(OBJDIR)/mmap.o
OBJ+=$(OBJDIR)/mprotect.o
OBJ+=$(OBJDIR)/_init.o
OBJ+=$(OBJDIR)/pread.o
OBJ+=$(OBJDIR)/pwrite.o
OBJ+=$(OBJDIR)/preadv.o
OBJ+=$(OBJDIR)/pwritev.o
OBJ+=$(OBJDIR)/read.o
OBJ+=$(OBJDIR)/readv.o
OBJ+=$(OBJDIR)/write.o
OBJ+=$(OBJDIR)/writev.o
HEADERS=$(CRTDIR) $(OBJDIR)
INCLUDES=-I../include -I../../franken/include -I.
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-fno-stack-protector
RANLIB?=ranlib

default:			$(OBJ)

$(OBJDIR):			
				mkdir -p $(OBJDIR)

$(CRTDIR):			
				mkdir -p $(CRTDIR)

$(CRTDIR)/crt.o:		crt.S $(CRTDIR)
				$(COMPILE.S) -o $@ crt.S

$(CRTDIR)/crt0.o:		$(CRTDIR)
				printf "\n" | $(COMPILE.c) -o $@ -x c -

$(CRTDIR)/crti.o:		$(CRTDIR)
				printf "\n" | $(COMPILE.c) -o $@ -x c -

$(CRTDIR)/crtn.o:		$(CRTDIR)
				printf "\n" | $(COMPILE.c) -o $@ -x c -

$(CRTDIR)/crtbegin.o:		$(CRTDIR)
				printf "\n" | $(COMPILE.c) -o $@ -x c -

$(CRTDIR)/crtbeginT.o:		$(CRTDIR)
				printf "\n" | $(COMPILE.c) -o $@ -x c -

$(CRTDIR)/crtend.o:		$(CRTDIR)
				printf "\n" | $(COMPILE.c) -o $@ -x c -

$(OBJDIR)/clock_getres.o:	clock_getres.c $(HEADERS)
				$(COMPILE.c) -o $@ clock_getres.c

$(OBJDIR)/clock_gettime.o:	clock_gettime.c $(HEADERS)
				$(COMPILE.c) -o $@ clock_gettime.c

$(OBJDIR)/clock_nanosleep.o:	clock_nanosleep.c $(HEADERS)
				$(COMPILE.c) -o $@ clock_nanosleep.c

$(OBJDIR)/_exit.o:		_exit.c $(HEADERS)
				$(COMPILE.c) -o $@ _exit.c

$(OBJDIR)/fcntl.o:		fcntl.c $(HEADERS)
				$(COMPILE.c) -o $@ fcntl.c

$(OBJDIR)/fstat.o:		fstat.c $(HEADERS)
				$(COMPILE.c) -o $@ fstat.c

$(OBJDIR)/fsync.o:		fsync.c $(HEADERS)
				$(COMPILE.c) -o $@ fsync.c

$(OBJDIR)/getpagesize.o:	getpagesize.c $(HEADERS)
				$(COMPILE.c) -o $@ getpagesize.c

$(OBJDIR)/getrandom.o:		getrandom.c $(HEADERS)
				$(COMPILE.c) -o $@ getrandom.c

$(OBJDIR)/kill.o:		kill.c $(HEADERS)
				$(COMPILE.c) -o $@ kill.c

$(OBJDIR)/_init.o:		_init.c $(HEADERS)
				$(COMPILE.c) -o $@ _init.c

$(OBJDIR)/mmap.o:		mmap.c $(HEADERS)
				$(COMPILE.c) -o $@ mmap.c

$(OBJDIR)/mprotect.o:		mprotect.c
				$(COMPILE.c) -o $@ mprotect.c

$(OBJDIR)/pread.o:		pread.c $(HEADERS)
				$(COMPILE.c) -o $@ pread.c

$(OBJDIR)/preadv.o:		preadv.c $(HEADERS)
				$(COMPILE.c) -o $@ preadv.c

$(OBJDIR)/pwrite.o:		pwrite.c $(HEADERS)
				$(COMPILE.c) -o $@ pwrite.c

$(OBJDIR)/pwritev.o:		pwritev.c $(HEADERS)
				$(COMPILE.c) -o $@ pwritev.c

$(OBJDIR)/read.o:		read.c $(HEADERS)
				$(COMPILE.c) -o $@ read.c

$(OBJDIR)/readv.o:		readv.c $(HEADERS)
				$(COMPILE.c) -o $@ readv.c

$(OBJDIR)/write.o:		write.c $(HEADERS)
				$(COMPILE.c) -o $@ write.c

$(OBJDIR)/writev.o:		writev.c $(HEADERS)
				$(COMPILE.c) -o $@ writev.c

.PHONY:				clean
clean:		
				rm -f $(OBJ)
