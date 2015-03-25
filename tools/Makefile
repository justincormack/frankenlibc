COMPILE.c?=$(CC) -c $(CPPFLAGS) $(CFLAGS)
OS?=linux
OBJDIR=../rumpobj/tools
BINDIR=../rump/bin
OUT=$(BINDIR)/rumprun
OBJ=$(OBJDIR)/rumprun.o $(OBJDIR)/${OS}.o
INC=rumprun.h
DEPS=$(INC) $(OBJDIR)

default:		$(OS)

$(OBJDIR):		
			mkdir -p $(OBJDIR)

$(OBJDIR)/rumprun.o:	rumprun.c $(DEPS)
			$(COMPILE.c) -o $@ rumprun.c

$(OBJDIR)/linux.o:	linux.c $(DEPS)
			$(COMPILE.c) -o $@ linux.c

$(OBJDIR)/netbsd.o:	netbsd.c $(DEPS)
			$(COMPILE.c) -o $@ netbsd.c

$(OBJDIR)/freebsd.o:	freebsd.c $(DEPS)
			$(COMPILE.c) -o $@ freebsd.c

linux:			$(OBJ)
			$(CC) $(CPPFLAGS) $(CFLAGS) $(OBJ) -o $(BINDIR)/rumprun $(LDLIBS) 

freebsd:		$(OBJ)
			$(CC) $(CPPFLAGS) $(CFLAGS) $(OBJ) -o $(BINDIR)/rumprun

netbsd:			$(OBJ)
			$(CC) $(CPPFLAGS) $(CFLAGS) $(OBJ) -o $(BINDIR)/rumprun

qemu-arm:		

.PHONY:			clean linux netbsd freebsd
clean:		
			rm -f $(OUT) $(OBJDIR)/*.o
