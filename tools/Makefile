COMPILE.c?=$(CC) -c $(CPPFLAGS) $(CFLAGS)
OS?=linux
RUMPOBJ?=../rumpobj
OBJDIR=$(RUMPOBJ)/tools
RUMP?=$(RUMPOBJ)/rump
BINDIR=$(RUMP)/bin
OUT=$(BINDIR)/rumprun
OBJ=$(OBJDIR)/rumprun.o $(OBJDIR)/${OS}.o
INC=rumprun.h
DEPS=$(INC) $(OBJDIR) $(BINDIR)

default:		$(OS)

$(OBJDIR):		
			mkdir -p $(OBJDIR)

$(BINDIR):
			mkdir -p $(BINDIR)

$(OBJDIR)/rumprun.o:	rumprun.c $(DEPS)
			$(COMPILE.c) -o $@ rumprun.c

$(OBJDIR)/linux.o:	linux.c $(DEPS)
			$(COMPILE.c) -o $@ linux.c

$(OBJDIR)/netbsd.o:	netbsd.c $(DEPS)
			$(COMPILE.c) -o $@ netbsd.c

$(OBJDIR)/freebsd.o:	freebsd.c $(DEPS)
			$(COMPILE.c) -o $@ freebsd.c

linux:			$(OBJ)
			$(CC) $(LDFLAGS) $(LDSTATIC) $(OBJ) -o $(BINDIR)/rumprun $(LDLIBS)

freebsd:		$(OBJ)
			$(CC) $(LDFLAGS) $(LDSTATIC) $(OBJ) -o $(BINDIR)/rumprun

netbsd:			$(OBJ)
			$(CC) $(LDFLAGS) $(LDSTATIC) $(OBJ) -o $(BINDIR)/rumprun

qemu-arm:		qemu-arm.sh
			cp qemu-arm.sh $(OUT)

.PHONY:			clean linux netbsd freebsd
clean:		
			rm -f $(OUT) $(OBJDIR)/*.o
