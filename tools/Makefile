COMPILE.c?=$(CC) -c $(CPPFLAGS) $(CFLAGS)
OS?=linux
OBJDIR=../rumpobj/tools
BINDIR=../rump/bin
OUT=$(BINDIR)/rumprun
OBJ=$(OBJDIR)/rumprun.o $(OBJDIR)/${OS}.o

default:		$(OS)

$(OBJDIR):		
			mkdir -p $(OBJDIR)

$(OBJDIR)/rumprun.o:	rumprun.c $(OBJDIR)
			$(COMPILE.c) -o $@ rumprun.c

$(OBJDIR)/linux.o:	linux.c $(OBJDIR)
			$(COMPILE.c) -o $@ linux.c

$(OBJDIR)/netbsd.o:	netbsd.c $(OBJDIR)
			$(COMPILE.c) -o $@ netbsd.c

$(OBJDIR)/freebsd.o:	freebsd.c $(OBJDIR)
			$(COMPILE.c) -o $@ freebsd.c

linux:			$(OBJ)
			$(CC) $(CPPFLAGS) $(CFLAGS) $(OBJ) -o $(BINDIR)/rumprun -lseccomp 

netbsd:			$(OBJ)
			$(CC) $(CPPFLAGS) $(CFLAGS) $(OBJ) -o $(BINDIR)/rumprun

freebsd:		$(OBJ)
			$(CC) $(CPPFLAGS) $(CFLAGS) $(OBJ) -o $(BINDIR)/rumprun

.PHONY:			clean linux netbsd freebsd
clean:		
			rm -f $(OUT) $(OBJ)
