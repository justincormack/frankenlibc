OS?=linux
GDIRS=generic crt lwp stubs thread
DIRS=$(OS) $(GDIRS)
LIBDIR=../rump/lib
LIB=$(LIBDIR)/libfranken.a
OBJDIR=../rumpobj/libc
RANLIB?=ranlib

.PHONY:		$(DIRS) clean test

default:	$(DIRS) $(LIB)

$(DIRS):	
		$(MAKE) OS=$(OS) -C $@

$(LIB):		$(DIRS)
		mkdir -p $(OBJDIR)
		$(AR) cr $@ $(OBJDIR)/*.o
		$(RANLIB) $@

test:		default
		$(MAKE) -C $@

clean:		
		for dir in freebsd linux netbsd $(GDIRS) test; \
		do \
			$(MAKE) -C $$dir OS= clean; \
		done
		rm -f $(LIB)
