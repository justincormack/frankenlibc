COMPILE.c?=$(CC) -c $(CPPFLAGS) $(CFLAGS)
COMPILE.S?=$(CC) -c $(CPPFLAGS) $(ASFLAGS)
RUMPOBJ?=../../rumpobj
OBJDIR=$(RUMPOBJ)/libc
OBJ+=$(OBJDIR)/abort.o
OBJ+=$(OBJDIR)/assert.o $(OBJDIR)/atoi.o
OBJ+=$(OBJDIR)/errno.o
OBJ+=$(OBJDIR)/getenv.o $(OBJDIR)/isspace.o
OBJ+=$(OBJDIR)/memcpy.o $(OBJDIR)/memset.o
OBJ+=$(OBJDIR)/putchar.o $(OBJDIR)/raise.o
OBJ+=$(OBJDIR)/strchr.o $(OBJDIR)/strcmp.o
OBJ+=$(OBJDIR)/strcpy.o $(OBJDIR)/strdup.o
OBJ+=$(OBJDIR)/strlen.o $(OBJDIR)/strncmp.o
OBJ+=$(OBJDIR)/strncpy.o
INCLUDES=-I../include
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-fno-stack-protector
DEPS=$(OBJDIR)

default:			$(OBJ)

$(OBJDIR):			
				mkdir -p $(OBJDIR)

$(OBJDIR)/abort.o:		abort.c $(DEPS)
				$(COMPILE.c) -o $@ abort.c

$(OBJDIR)/assert.o:		assert.c $(DEPS)
				$(COMPILE.c) -o $@ assert.c

$(OBJDIR)/atoi.o:		atoi.c $(DEPS)
				$(COMPILE.c) -o $@ atoi.c

$(OBJDIR)/errno.o:		errno.c $(DEPS)
				$(COMPILE.c) -o $@ errno.c

$(OBJDIR)/getenv.o:		getenv.c $(DEPS)
				$(COMPILE.c) -o $@ getenv.c

$(OBJDIR)/isspace.o:		isspace.c $(DEPS)
				$(COMPILE.c) -o $@ isspace.c

$(OBJDIR)/memcpy.o:		memcpy.c $(DEPS)
				$(COMPILE.c) -o $@ memcpy.c

$(OBJDIR)/memset.o:		memset.c $(DEPS)
				$(COMPILE.c) -o $@ memset.c

$(OBJDIR)/putchar.o:		putchar.c $(DEPS)
				$(COMPILE.c) -o $@ putchar.c

$(OBJDIR)/raise.o:		raise.c $(DEPS)
				$(COMPILE.c) -o $@ raise.c

$(OBJDIR)/strchr.o:		strchr.c $(DEPS)
				$(COMPILE.c) -o $@ strchr.c

$(OBJDIR)/strcmp.o:		strcmp.c $(DEPS)
				$(COMPILE.c) -o $@ strcmp.c

$(OBJDIR)/strcpy.o:		strcpy.c $(DEPS)
				$(COMPILE.c) -o $@ strcpy.c

$(OBJDIR)/strdup.o:		strdup.c $(DEPS)
				$(COMPILE.c) -o $@ strdup.c

$(OBJDIR)/strlen.o:		strlen.c $(DEPS)
				$(COMPILE.c) -o $@ strlen.c

$(OBJDIR)/strncmp.o:		strncmp.c $(DEPS)
				$(COMPILE.c) -o $@ strncmp.c

$(OBJDIR)/strncpy.o:		strncpy.c $(DEPS)
				$(COMPILE.c) -o $@ strncpy.c

.PHONY:				clean
clean:		
				rm -f $(OBJ)
