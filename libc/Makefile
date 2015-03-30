OS?=linux
GDIRS=generic crt lwp stubs thread init ucontext malloc
DIRS=$(OS) $(GDIRS)
RUMP?=../rump
LIBDIR=$(RUMP)/lib
LIB=$(LIBDIR)/libfranken.a
RUMPOBJ?=../rumpobj
OBJDIR=$(RUMPOBJ)/libc
RANLIB?=ranlib

.PHONY:		$(DIRS) clean test

default:	$(DIRS) $(LIB)

$(DIRS):	
		$(MAKE) OS=$(OS) -C $@

deterministic:	$(DIRS)
		$(MAKE) -C $@ clean
		$(MAKE) -C $@

$(LIB):		$(DIRS) $(DETERMINISTIC)
		mkdir -p $(OBJDIR)
		$(AR) cr $@ $(OBJDIR)/*.o
		$(RANLIB) $@

test:		default
		$(MAKE) -C $@

clean:		
		for dir in freebsd linux netbsd qemu-arm $(GDIRS) test deterministic; \
		do \
			$(MAKE) -C $$dir OS= clean; \
		done
		rm -f $(LIB)
