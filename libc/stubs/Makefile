OBJDIR=../../obj/libc
OBJ=$(OBJDIR)/stub___errno.o $(OBJDIR)/stub_execve.o $(OBJDIR)/stub___fork.o $(OBJDIR)/stub_madvise.o $(OBJDIR)/stub_minherit.o $(OBJDIR)/stub__mmap.o $(OBJDIR)/stub___msync13.o $(OBJDIR)/stub_setpriority.o $(OBJDIR)/stub___sigaction_sigtramp.o $(OBJDIR)/stub___sigprocmask14.o $(OBJDIR)/stub___vfork14.o $(OBJDIR)/stub___wait450.o
INCLUDES=-I../include
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-fno-stack-protector
HEADERS=stub.h

default:			$(OBJDIR) $(OBJ)

$(OBJDIR):			
				mkdir -p $(OBJDIR)

$(OBJDIR)/stub___errno.o:	__errno.c
				$(COMPILE.c) -o $@ __errno.c

$(OBJDIR)/stub_execve.o:	execve.c
				$(COMPILE.c) -o $@ execve.c

$(OBJDIR)/stub___fork.o:	__fork.c
				$(COMPILE.c) -o $@ __fork.c

$(OBJDIR)/stub_madvise.o:	madvise.c
				$(COMPILE.c) -o $@ madvise.c

$(OBJDIR)/stub_minherit.o:	minherit.c
				$(COMPILE.c) -o $@ minherit.c

$(OBJDIR)/stub__mmap.o:		_mmap.c
				$(COMPILE.c) -o $@ _mmap.c

$(OBJDIR)/stub___msync13.o:	__msync13.c
				$(COMPILE.c) -o $@ __msync13.c

$(OBJDIR)/stub_setpriority.o:	setpriority.c
				$(COMPILE.c) -o $@ setpriority.c

$(OBJDIR)/stub___sigaction_sigtramp.o:	__sigaction_sigtramp.c
				$(COMPILE.c) -o $@ __sigaction_sigtramp.c

$(OBJDIR)/stub___sigprocmask14.o:	__sigprocmask14.c
				$(COMPILE.c) -o $@ __sigprocmask14.c

$(OBJDIR)/stub___sigsuspend14.o:	__sigsuspend14.c
				$(COMPILE.c) -o $@ __sigsuspend14.c

$(OBJDIR)/stub___vfork14.o:	__vfork14.c
				$(COMPILE.c) -o $@ __vfork14.c

$(OBJDIR)/stub___wait450.o:	__wait450.c
				$(COMPILE.c) -o $@ __wait450.c

.PHONY:				clean
clean:		
				rm -f $(OBJ)
