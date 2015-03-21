COMPILE.c?=$(CC) -c $(CPPFLAGS) $(CFLAGS)
COMPILE.S?=$(CC) -c $(CPPFLAGS) $(ASFLAGS)
OBJDIR=../../rumpobj/libc
OBJ+=$(OBJDIR)/__franken_start_main.o
OBJ+=$(OBJDIR)/abort.o $(OBJDIR)/aligned_alloc.o
OBJ+=$(OBJDIR)/assert.o $(OBJDIR)/atoi.o
OBJ+=$(OBJDIR)/calloc.o $(OBJDIR)/errno.o $(OBJDIR)/_Exit.o
OBJ+=$(OBJDIR)/getenv.o $(OBJDIR)/isspace.o
OBJ+=$(OBJDIR)/malloc.o $(OBJDIR)/memcpy.o $(OBJDIR)/memset.o
OBJ+=$(OBJDIR)/posix_memalign.o $(OBJDIR)/putchar.o $(OBJDIR)/raise.o
OBJ+=$(OBJDIR)/strchr.o $(OBJDIR)/strcmp.o $(OBJDIR)/strcpy.o $(OBJDIR)/strdup.o
OBJ+=$(OBJDIR)/strlen.o $(OBJDIR)/strncmp.o $(OBJDIR)/strncpy.o
INCLUDES=-I../include
RUMPINC=-I../../rump/include
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-fno-stack-protector

default:			$(OBJDIR) $(OBJ)

$(OBJDIR):			
				mkdir -p $(OBJDIR)

$(OBJDIR)/__franken_start_main.o:	__franken_start_main.c
				$(COMPILE.c) -o $@ __franken_start_main.c

$(OBJDIR)/abort.o:		abort.c
				$(COMPILE.c) -o $@ abort.c

$(OBJDIR)/aligned_alloc.o:	aligned_alloc.c
				$(COMPILE.c) -o $@ aligned_alloc.c

$(OBJDIR)/assert.o:		assert.c
				$(COMPILE.c) -o $@ assert.c

$(OBJDIR)/atoi.o:		atoi.c
				$(COMPILE.c) -o $@ atoi.c

$(OBJDIR)/calloc.o:		calloc.c
				$(COMPILE.c) -o $@ calloc.c

$(OBJDIR)/errno.o:		errno.c
				$(COMPILE.c) -o $@ errno.c

$(OBJDIR)/_Exit.o:		_Exit.c
				$(COMPILE.c) -o $@ _Exit.c

$(OBJDIR)/getenv.o:		getenv.c
				$(COMPILE.c) -o $@ getenv.c

$(OBJDIR)/isspace.o:		isspace.c
				$(COMPILE.c) -o $@ isspace.c

$(OBJDIR)/malloc.o:		malloc.c
				$(COMPILE.c) -o $@ malloc.c

$(OBJDIR)/memcpy.o:		memcpy.c
				$(COMPILE.c) -o $@ memcpy.c

$(OBJDIR)/memset.o:		memset.c
				$(COMPILE.c) -o $@ memset.c

$(OBJDIR)/posix_memalign.o:	posix_memalign.c
				$(COMPILE.c) -o $@ posix_memalign.c

$(OBJDIR)/putchar.o:		putchar.c
				$(COMPILE.c) -o $@ putchar.c

$(OBJDIR)/raise.o:		raise.c
				$(COMPILE.c) -o $@ raise.c

$(OBJDIR)/strchr.o:		strchr.c
				$(COMPILE.c) -o $@ strchr.c

$(OBJDIR)/strcmp.o:		strcmp.c
				$(COMPILE.c) -o $@ strcmp.c

$(OBJDIR)/strcpy.o:		strcpy.c
				$(COMPILE.c) -o $@ strcpy.c

$(OBJDIR)/strdup.o:		strdup.c
				$(COMPILE.c) -o $@ strdup.c

$(OBJDIR)/strlen.o:		strlen.c
				$(COMPILE.c) -o $@ strlen.c

$(OBJDIR)/strncmp.o:		strncmp.c
				$(COMPILE.c) -o $@ strncmp.c

$(OBJDIR)/strncpy.o:		strncpy.c
				$(COMPILE.c) -o $@ strncpy.c

.PHONY:				clean
clean:		
				rm -f $(OBJ)
