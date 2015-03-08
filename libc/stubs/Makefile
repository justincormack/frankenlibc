COMPILE.c?=$(CC) -c $(CPPFLAGS) $(CFLAGS)
COMPILE.S?=$(CC) -c $(CPPFLAGS) $(ASFLAGS)
OBJDIR=../../rumpobj/libc
OBJ=$(OBJDIR)/stub___cerror.o $(OBJDIR)/stub___errno.o
OBJ+=$(OBJDIR)/stub_execve.o
OBJ+=$(OBJDIR)/stub___fork.o $(OBJDIR)/stub__getcontext.o
OBJ+=$(OBJDIR)/stub_getpriority.o $(OBJDIR)/stub___getrusage50.o
OBJ+=$(OBJDIR)/stub_kill.o $(OBJDIR)/stub___lfs_segwait50.o
OBJ+=$(OBJDIR)/stub_madvise.o $(OBJDIR)/stub___minbrk.o
OBJ+=$(OBJDIR)/stub_minherit.o
OBJ+=$(OBJDIR)/stub_mlock.o $(OBJDIR)/stub_mlockall.o
OBJ+=$(OBJDIR)/stub_mmap.o $(OBJDIR)/stub__mmap.o
OBJ+=$(OBJDIR)/stub___msgctl50.o $(OBJDIR)/stub___msync13.o
OBJ+=$(OBJDIR)/stub___mq_timedreceive50.o $(OBJDIR)/stub___mq_timedsend50.o
OBJ+=$(OBJDIR)/stub_munlock.o $(OBJDIR)/stub_munlockall.o
OBJ+=$(OBJDIR)/stub___ntp_gettime50.o $(OBJDIR)/stub_posix_spawn.o
OBJ+=$(OBJDIR)/stub_profil.o $(OBJDIR)/stub__sbrk.o
OBJ+=$(OBJDIR)/stub__sched_getaffinity.o $(OBJDIR)/stub__sched_getparam.o
OBJ+=$(OBJDIR)/stub__sched_setaffinity.o $(OBJDIR)/stub__sched_setparam.o
OBJ+=$(OBJDIR)/stub___shmctl50.o $(OBJDIR)/stub_____semctl50.o
OBJ+=$(OBJDIR)/stub_setcontext.o $(OBJDIR)/stub_setpriority.o
OBJ+=$(OBJDIR)/stub___sigaltstack14.o $(OBJDIR)/stub___sigaction_sigtramp.o
OBJ+=$(OBJDIR)/stub___sigprocmask14.o $(OBJDIR)/stub_sigqueueinfo.o
OBJ+=$(OBJDIR)/stub___sigsuspend14.o $(OBJDIR)/stub_____sigtimedwait50.o
OBJ+=$(OBJDIR)/stub_swapctl.o $(OBJDIR)/stub_uuidgen.o
OBJ+=$(OBJDIR)/stub___vfork14.o $(OBJDIR)/stub___wait450.o
INCLUDES=-I../include
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-fno-stack-protector
HEADERS=stub.h

default:				$(OBJDIR) $(OBJ)

$(OBJDIR):			
					mkdir -p $(OBJDIR)

$(OBJDIR)/stub___cerror.o:		__cerror.c
					$(COMPILE.c) -o $@ __cerror.c

$(OBJDIR)/stub___errno.o:		__errno.c
					$(COMPILE.c) -o $@ __errno.c

$(OBJDIR)/stub_execve.o:		execve.c
					$(COMPILE.c) -o $@ execve.c

$(OBJDIR)/stub___fork.o:		__fork.c
					$(COMPILE.c) -o $@ __fork.c

$(OBJDIR)/stub__getcontext.o:		_getcontext.c
					$(COMPILE.c) -o $@ _getcontext.c

$(OBJDIR)/stub_getpriority.o:		getpriority.c
					$(COMPILE.c) -o $@ getpriority.c

$(OBJDIR)/stub___getrusage50.o:		__getrusage50.c
					$(COMPILE.c) -o $@ __getrusage50.c

$(OBJDIR)/stub_kill.o:			kill.c
					$(COMPILE.c) -o $@ kill.c

$(OBJDIR)/stub___lfs_segwait50.o:	__lfs_segwait50.c
					$(COMPILE.c) -o $@ __lfs_segwait50.c

$(OBJDIR)/stub_madvise.o:		madvise.c
					$(COMPILE.c) -o $@ madvise.c

$(OBJDIR)/stub___minbrk.o:		__minbrk.c
					$(COMPILE.c) -o $@ __minbrk.c

$(OBJDIR)/stub_minherit.o:		minherit.c
					$(COMPILE.c) -o $@ minherit.c

$(OBJDIR)/stub_mlock.o:			mlock.c
					$(COMPILE.c) -o $@ mlock.c

$(OBJDIR)/stub_mlockall.o:		mlockall.c
					$(COMPILE.c) -o $@ mlockall.c

$(OBJDIR)/stub_mmap.o:			mmap.c
					$(COMPILE.c) -o $@ mmap.c

$(OBJDIR)/stub__mmap.o:			_mmap.c
					$(COMPILE.c) -o $@ _mmap.c

$(OBJDIR)/stub___msgctl50.o:		__msgctl50.c
					$(COMPILE.c) -o $@ __msgctl50.c

$(OBJDIR)/stub___msync13.o:		__msync13.c
					$(COMPILE.c) -o $@ __msync13.c

$(OBJDIR)/stub___mq_timedreceive50.o:	__mq_timedreceive50.c
					$(COMPILE.c) -o $@ __mq_timedreceive50.c

$(OBJDIR)/stub___mq_timedsend50.o:	__mq_timedsend50.c
					$(COMPILE.c) -o $@ __mq_timedsend50.c

$(OBJDIR)/stub_munlock.o:		munlock.c
					$(COMPILE.c) -o $@ munlock.c

$(OBJDIR)/stub_munlockall.o:		munlockall.c
					$(COMPILE.c) -o $@ munlockall.c

$(OBJDIR)/stub___ntp_gettime50.o:	__ntp_gettime50.c
					$(COMPILE.c) -o $@ __ntp_gettime50.c

$(OBJDIR)/stub_posix_spawn.o:		posix_spawn.c
					$(COMPILE.c) -o $@ posix_spawn.c

$(OBJDIR)/stub_profil.o:		profil.c
					$(COMPILE.c) -o $@ profil.c

$(OBJDIR)/stub__sbrk.o:			_sbrk.c
					$(COMPILE.c) -o $@ _sbrk.c

$(OBJDIR)/stub___shmctl50.o:		__shmctl50.c
					$(COMPILE.c) -o $@ __shmctl50.c

$(OBJDIR)/stub__sched_getaffinity.o:	_sched_getaffinity.c
					$(COMPILE.c) -o $@ _sched_getaffinity.c

$(OBJDIR)/stub__sched_getparam.o:	_sched_getparam.c
					$(COMPILE.c) -o $@ _sched_getparam.c

$(OBJDIR)/stub__sched_setaffinity.o:	_sched_setaffinity.c
					$(COMPILE.c) -o $@ _sched_setaffinity.c

$(OBJDIR)/stub__sched_setparam.o:	_sched_setparam.c
					$(COMPILE.c) -o $@ _sched_setparam.c

$(OBJDIR)/stub_____semctl50.o:		____semctl50.c
					$(COMPILE.c) -o $@ ____semctl50.c

$(OBJDIR)/stub_setcontext.o:		setcontext.c
					$(COMPILE.c) -o $@ setcontext.c

$(OBJDIR)/stub_setpriority.o:		setpriority.c
					$(COMPILE.c) -o $@ setpriority.c

$(OBJDIR)/stub___sigaction_sigtramp.o:	__sigaction_sigtramp.c
					$(COMPILE.c) -o $@ __sigaction_sigtramp.c

$(OBJDIR)/stub___sigaltstack14.o:	__sigaltstack14.c
					$(COMPILE.c) -o $@ __sigaltstack14.c

$(OBJDIR)/stub___sigprocmask14.o:	__sigprocmask14.c
					$(COMPILE.c) -o $@ __sigprocmask14.c

$(OBJDIR)/stub_sigqueueinfo.o:		sigqueueinfo.c
					$(COMPILE.c) -o $@ sigqueueinfo.c

$(OBJDIR)/stub___sigsuspend14.o:	__sigsuspend14.c
					$(COMPILE.c) -o $@ __sigsuspend14.c

$(OBJDIR)/stub_____sigtimedwait50.o:	____sigtimedwait50.c
					$(COMPILE.c) -o $@ ____sigtimedwait50.c

$(OBJDIR)/stub_swapctl.o:		swapctl.c
					$(COMPILE.c) -o $@ swapctl.c

$(OBJDIR)/stub_uuidgen.o:		uuidgen.c
					$(COMPILE.c) -o $@ uuidgen.c

$(OBJDIR)/stub___vfork14.o:		__vfork14.c
					$(COMPILE.c) -o $@ __vfork14.c

$(OBJDIR)/stub___wait450.o:		__wait450.c
					$(COMPILE.c) -o $@ __wait450.c

.PHONY:					clean
clean:		
					rm -f $(OBJ)
