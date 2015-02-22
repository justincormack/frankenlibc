OBJDIR=../../obj/libc
OBJ=$(OBJDIR)/stub___fork.o $(OBJDIR)/stub_madvise.o $(OBJDIR)/stub_minherit.o $(OBJDIR)/stub_setpriority.o $(OBJDIR)/stub___sigaction_sigtramp.o $(OBJDIR)/stub___sigprocmask14.o
INCLUDES=-I../include
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-fno-stack-protector

default:			$(OBJDIR) $(OBJ)

$(OBJDIR):			
				mkdir -p $(OBJDIR)

$(OBJDIR)/stub___fork.o:	__fork.c
				$(COMPILE.c) -o $@ __fork.c

$(OBJDIR)/stub_madvise.o:	madvise.c
				$(COMPILE.c) -o $@ madvise.c

$(OBJDIR)/stub_minherit.o:	minherit.c
				$(COMPILE.c) -o $@ minherit.c

$(OBJDIR)/stub_setpriority.o:	setpriority.c
				$(COMPILE.c) -o $@ setpriority.c

$(OBJDIR)/stub___sigaction_sigtramp.o:	__sigaction_sigtramp.c
				$(COMPILE.c) -o $@ __sigaction_sigtramp.c

$(OBJDIR)/stub___sigprocmask14.o:	__sigprocmask14.c
				$(COMPILE.c) -o $@ __sigprocmask14.c

.PHONY:				clean
clean:		
				rm -f $(OBJ)
