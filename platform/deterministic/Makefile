COMPILE.c?=$(CC) -c $(CPPFLAGS) $(CFLAGS)
COMPILE.S?=$(CC) -c $(CPPFLAGS) $(ASFLAGS)
RUMPOBJ?=../../rumpobj
OBJDIR=$(RUMPOBJ)/platform
OBJ=$(OBJDIR)/clock_getres.o
OBJ+=$(OBJDIR)/clock_gettime.o
OBJ+=$(OBJDIR)/clock_nanosleep.o
OBJ+=$(OBJDIR)/getrandom.o
CLEANOBJ=$(OBJ) $(OBJDIR)/__clock_getres.o $(OBJDIR)/__clock_gettime.o
CLEANOBJ+=$(OBJDIR)/__clock_nanosleep.o $(OBJDIR)/__getrandom.o
INCLUDES=-I../include -I../../libc/include
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-fno-stack-protector

default:			$(CRTDIR) $(OBJDIR) $(OBJ)

$(OBJDIR):			
				mkdir -p $(OBJDIR)

$(OBJDIR)/clock_getres.o:	clock_getres.c $(HEADERS)
				$(COMPILE.c) -o $@ clock_getres.c

$(OBJDIR)/clock_gettime.o:	clock_gettime.c $(HEADERS)
				$(COMPILE.c) -o $@ clock_gettime.c

$(OBJDIR)/clock_nanosleep.o:	clock_nanosleep.c $(HEADERS)
				$(COMPILE.c) -o $@ clock_nanosleep.c

$(OBJDIR)/getrandom.o:		getrandom.c $(HEADERS)
				$(COMPILE.c) -o $@ getrandom.c

.PHONY:				clean
clean:		
				rm -f $(CLEANOBJ)
