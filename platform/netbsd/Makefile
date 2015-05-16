COMPILE.c?=$(CC) -c $(CPPFLAGS) $(CFLAGS)
COMPILE.S?=$(CC) -c $(CPPFLAGS) $(ASFLAGS)
RUMPOBJ?=../../rumpobj
OBJDIR=$(RUMPOBJ)/platform
RUMP?=$(RUMPOBJ)/rump
CRTDIR=$(RUMP)/lib
OBJ=$(CRTDIR)/crt0.o
OBJ+=$(CRTDIR)/crti.o $(CRTDIR)/crtn.o
OBJ+=$(CRTDIR)/crtbegin.o $(CRTDIR)/crtbeginT.o
OBJ+=$(CRTDIR)/crtend.o
OBJ+=$(OBJDIR)/clock_nanosleep.o
OBJ+=$(OBJDIR)/fstat.o
OBJ+=$(OBJDIR)/getpagesize.o
OBJ+=$(OBJDIR)/getrandom.o
OBJ+=$(OBJDIR)/___start.o
OBJ+=$(OBJDIR)/syscall.o
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

CRT=printf "" | ${CC} ${CFLAGS} -v -x c - -static -o /dev/null 2>&1| grep crti.o | tr ' ' '\n'
CRTI!=$(CRT) | grep crti.o
CRTN!=$(CRT) | grep crtn.o
CRTBEGIN!=$(CRT) | grep crtbegin.o || true
CRTBEGINT!=$(CRT) | grep crtbeginT.o || true
CRTEND!=$(CRT) | grep crtend.o

$(CRTDIR)/crti.o:		$(CRTDIR)
				cp $(CRTI) $@
				chmod u+w $@

$(CRTDIR)/crtn.o:		$(CRTDIR)
				cp $(CRTN) $@
				chmod u+w $@

$(CRTDIR)/crtbegin.o:		$(CRTDIR)
				$(CRT) | grep crtbegin.o && cp $(CRTBEGIN) $@ && chmod u+w $@ || true

$(CRTDIR)/crtbeginT.o:		$(CRTDIR)
				$(CRT) | grep crtbeginT.o && cp $(CRTBEGINT) $@ && chmod u+w $@ || true

$(CRTDIR)/crtend.o:		$(CRTDIR)
				cp $(CRTEND) $@
				chmod u+w $@

$(OBJDIR)/clock_nanosleep.o:	clock_nanosleep.c $(HEADERS)
				$(COMPILE.c) -o $@ clock_nanosleep.c

$(OBJDIR)/fstat.o:		fstat.c $(HEADERS)
				$(COMPILE.c) -o $@ fstat.c

$(OBJDIR)/getpagesize.o:	getpagesize.c $(HEADERS)
				$(COMPILE.c) -o $@ getpagesize.c

$(OBJDIR)/getrandom.o:		getrandom.c $(HEADERS)
				$(COMPILE.c) -o $@ getrandom.c

$(OBJDIR)/___start.o:		___start.c $(HEADERS)
				$(COMPILE.c) -o $@ ___start.c

$(OBJDIR)/syscall.o:		syscall.S $(HEADERS)
				$(COMPILE.S) -o $@ syscall.S

.PHONY:				clean
clean:		
				rm -f rm -f $(OBJDIR)/*.o $(CRTDIR)/*.o
