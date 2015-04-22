RUMPOBJ?=../rumpobj
RUMP?=$(RUMPOBJ)/rump
LIBDIR=$(RUMP)/lib
LIB=$(LIBDIR)/librumpnet_virtif.a
OBJDIR=$(RUMPOBJ)/libvirtif
INC=-nostdinc -I../franken/include -I../franken/ucontext -I../franken/init -I../franken/thread -I../platform/include -I../librumpuser
CFLAGS+=-fno-stack-protector
USER_FLAGS=$(CPPFLAGS) -DVIRTIF_BASE=virt $(INC) $(CFLAGS)
RANLIB?=ranlib
RUMPMAKE?=$(RUMPOBJ)/tooldir/rumpmake

OBJ=$(OBJDIR)/if_virt.o $(OBJDIR)/virtif_user.o

default:			$(LIB)

$(OBJDIR):
				mkdir -p $@

$(LIBDIR):
				mkdir -p $@

$(OBJDIR)/if_virt.o:		if_virt.c if_virt.h $(OBJDIR)
				$(RUMPMAKE) -f Makefile.rump
				cp if_virt.o $@
				$(RUMPMAKE) -f Makefile.rump clean

$(OBJDIR)/virtif_user.o:	virtif_user.c virtif_user.h $(OBJDIR)
				$(CC) $(USER_FLAGS) -c virtif_user.c -o $@

$(LIB):				$(OBJ) $(LIBDIR)
				$(AR) cr $@ $(OBJ)
				$(RANLIB) $@

.PHONY:				clean
clean:
				$(RUMPMAKE) -f Makefile.rump clean
				rm -f $(OBJ) $(LIB)
