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

$(OBJDIR)/dummy.o:	dummy.c $(OBJDIR)
			$(COMPILE.c) -o $@ dummy.c

$(OBJDIR)/freebsd.o:	freebsd.c $(OBJDIR)
			$(COMPILE.c) -o $@ freebsd.c

linux:			$(OBJ)
			$(CC) $(CPPFLAGS) $(CFLAGS) $(OBJ) -o $(BINDIR)/rumprun -lseccomp 

netbsd:			dummy

freebsd:		$(OBJ)
			$(CC) $(CPPFLAGS) $(CFLAGS) $(OBJ) -o $(BINDIR)/rumprun

dummy:			$(OBJDIR)/rumprun.o $(OBJDIR)/dummy.o
			$(CC) $(CPPFLAGS) $(CFLAGS) $(OBJDIR)/rumprun.o $(OBJDIR)/dummy.o -o $(BINDIR)/rumprun

.PHONY:			clean linux netbsd freebsd dummy
clean:		
			rm -f $(OUT) $(OBJDIR)/*.o
