COMPILE.c?=$(CC) -c $(CPPFLAGS) $(CFLAGS)
RUMPOBJ?=../rumpobj
OBJDIR=$(RUMPOBJ)/tools
RUMP?=$(RUMPOBJ)/rump
BINDIR=$(RUMP)/bin
OUT=$(BINDIR)/rumprun
OBJ=$(OBJDIR)/rumprun.o
INC=rumprun.h
DEPS=$(INC) $(OBJDIR) $(BINDIR)
PLATFORMS=freebsd linux netbsd qemu-arm

default:		linux

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

linux:			$(OBJ) $(OBJDIR)/linux.o
			$(CC) $(LDFLAGS) $(LDSTATIC) $(OBJ) $(OBJDIR)/linux.o -o $(BINDIR)/rumprun $(LDLIBS)

freebsd:		$(OBJ) $(OBJDIR)/freebsd.o
			$(CC) $(LDFLAGS) $(LDSTATIC) $(OBJ) $(OBJDIR)/freebsd.o -o $(BINDIR)/rumprun

netbsd:			$(OBJ) $(OBJDIR)/netbsd.o
			$(CC) $(LDFLAGS) $(LDSTATIC) $(OBJ) $(OBJDIR)/netbsd.o -o $(BINDIR)/rumprun

qemu-arm:		qemu-arm.sh
			cp qemu-arm.sh $(OUT)

.PHONY:			clean $(PLATFORMS)
clean:		
			rm -f $(OUT) $(OBJDIR)/*.o
