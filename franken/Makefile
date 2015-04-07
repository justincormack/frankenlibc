DIRS=libc crt lwp stubs thread init ucontext malloc
RUMPOBJ?=../rumpobj
RUMP?=$(RUMPOBJ)/rump
LIBDIR=$(RUMP)/lib
LIB=$(LIBDIR)/libfranken.a
OBJDIR=$(RUMPOBJ)/franken
RANLIB?=ranlib

.PHONY:		$(DIRS) clean test

default:	$(DIRS) $(LIB)

$(DIRS):	
		$(MAKE) -C $@

$(LIB):		$(DIRS)
		mkdir -p $(LIBDIR)
		$(AR) cr $@ $(OBJDIR)/*.o
		$(RANLIB) $@

test:		default
		$(MAKE) -C $@

clean:		
		for dir in $(GDIRS); \
		do \
			$(MAKE) -C $$dir clean; \
		done
		rm -f $(LIB)
