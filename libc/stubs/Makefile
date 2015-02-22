OBJDIR=../../obj/libc
OBJ=$(OBJDIR)/madvise.o $(OBJDIR)/setpriority.o $(OBJDIR)/__sigaction_sigtramp.o $(OBJDIR)/__sigprocmask14.o
INCLUDES=-I../include
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-fno-stack-protector

default:			$(OBJDIR) $(OBJ)

$(OBJDIR):			
				mkdir -p $(OBJDIR)

$(OBJDIR)/madvise.o:		madvise.c
				$(COMPILE.c) -o $@ madvise.c

$(OBJDIR)/setpriority.o:	setpriority.c
				$(COMPILE.c) -o $@ setpriority.c

$(OBJDIR)/__sigaction_sigtramp.o:	__sigaction_sigtramp.c
				$(COMPILE.c) -o $@ __sigaction_sigtramp.c

$(OBJDIR)/__sigprocmask14.o:	__sigprocmask14.c
				$(COMPILE.c) -o $@ __sigprocmask14.c

.PHONY:				clean
clean:		
				rm -f $(OBJ)
