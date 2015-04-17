COMPILE.c?=$(CC) -c $(CPPFLAGS) $(CFLAGS)
COMPILE.S?=$(CC) -c $(CPPFLAGS) $(ASFLAGS)
RUMPOBJ?=../../rumpobj
OBJDIR=$(RUMPOBJ)/stublibc
LIB=$(OBJDIR)/libc.a
OBJ+=$(OBJDIR)/abort.o
OBJ+=$(OBJDIR)/assert.o $(OBJDIR)/atoi.o
OBJ+=$(OBJDIR)/getenv.o
OBJ+=$(OBJDIR)/memcpy.o $(OBJDIR)/memset.o
OBJ+=$(OBJDIR)/strchr.o $(OBJDIR)/strcmp.o
OBJ+=$(OBJDIR)/strcpy.o $(OBJDIR)/strdup.o
OBJ+=$(OBJDIR)/strlen.o $(OBJDIR)/strncmp.o
OBJ+=$(OBJDIR)/strncpy.o
OBJ+=$(OBJDIR)/vsnprintf.o
OBJ+=$(OBJDIR)/rump.o

INCLUDES=-I../include -I../../platform/include
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-fno-stack-protector
DEPS=$(OBJDIR)
RANLIB?=ranlib

default:			$(LIB)

$(OBJDIR):			
				mkdir -p $(OBJDIR)

$(LIB):				$(OBJ)
				$(AR) cr $@ $(OBJ)
				$(RANLIB) $@

$(OBJDIR)/abort.o:		abort.c $(DEPS)
				$(COMPILE.c) -o $@ abort.c

$(OBJDIR)/assert.o:		assert.c $(DEPS)
				$(COMPILE.c) -o $@ assert.c

$(OBJDIR)/atoi.o:		atoi.c $(DEPS)
				$(COMPILE.c) -o $@ atoi.c

$(OBJDIR)/getenv.o:		getenv.c $(DEPS)
				$(COMPILE.c) -o $@ getenv.c

$(OBJDIR)/memcpy.o:		memcpy.c $(DEPS)
				$(COMPILE.c) -o $@ memcpy.c

$(OBJDIR)/memset.o:		memset.c $(DEPS)
				$(COMPILE.c) -o $@ memset.c

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

$(OBJDIR)/vsnprintf.o:		vsnprintf.c $(DEPS)
				$(COMPILE.c) -o $@ vsnprintf.c

$(OBJDIR)/rump.o:		rump.c $(DEPS)
				$(COMPILE.c) -o $@ rump.c

.PHONY:				clean
clean:		
				rm -f $(OBJ) $(LIB)
