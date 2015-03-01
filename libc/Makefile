OS?=linux
GDIRS=generic crt lwp stubs thread
DIRS=$(OS) $(GDIRS)
LIBDIR=../rump/lib
LIB=$(LIBDIR)/libfranken.a
OBJDIR=../rumpobj/libc

.PHONY:		$(DIRS) clean test

default:	$(DIRS) $(LIB)

$(DIRS):	
		$(MAKE) OS=$(OS) -C $@

$(LIB):		$(DIRS)
		mkdir -p $(OBJDIR)
		$(AR) cr $(LIB) $(OBJDIR)/*.o

test:		default
		$(MAKE) -C $@

clean:		
		for dir in linux netbsd $(GDIRS) test; \
		do \
			$(MAKE) -C $$dir OS= clean; \
		done
		rm -f $(LIB)
