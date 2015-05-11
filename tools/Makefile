COMPILE.c?=$(CC) -c $(CPPFLAGS) $(CFLAGS)
RUMPOBJ?=../rumpobj
OBJDIR=$(RUMPOBJ)/tools
RUMP?=$(RUMPOBJ)/rump
BINDIR=$(RUMP)/bin
BIN=$(BINDIR)/rexec
OBJ=$(OBJDIR)/rexec.o
INC=rexec.h
DEPS=$(INC) $(OBJDIR) $(BINDIR)
PLATFORMS=freebsd linux netbsd qemu-arm

default:		linux

$(OBJDIR):		
			mkdir -p $(OBJDIR)

$(BINDIR):
			mkdir -p $(BINDIR)

$(OBJDIR)/rexec.o:	rexec.c $(DEPS)
			$(COMPILE.c) -o $@ rexec.c

$(OBJDIR)/linux.o:	linux.c $(DEPS)
			$(COMPILE.c) -o $@ linux.c

$(OBJDIR)/netbsd.o:	netbsd.c $(DEPS)
			$(COMPILE.c) -o $@ netbsd.c

$(OBJDIR)/freebsd.o:	freebsd.c $(DEPS)
			$(COMPILE.c) -o $@ freebsd.c

linux:			$(OBJ) $(OBJDIR)/linux.o
			$(CC) $(LDFLAGS) $(LDSTATIC) $(OBJ) $(OBJDIR)/linux.o -o $(BIN) $(LDLIBS)

freebsd:		$(OBJ) $(OBJDIR)/freebsd.o
			$(CC) $(LDFLAGS) $(LDSTATIC) $(OBJ) $(OBJDIR)/freebsd.o -o $(BIN)

netbsd:			$(OBJ) $(OBJDIR)/netbsd.o
			$(CC) $(LDFLAGS) $(LDSTATIC) $(OBJ) $(OBJDIR)/netbsd.o -o $(BIN)

qemu-arm:		qemu-arm.sh
			cp qemu-arm.sh $(BIN)

.PHONY:			clean $(PLATFORMS)
clean:		
			rm -f $(BIN) $(OBJDIR)/*.o
