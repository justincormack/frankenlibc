OS?=linux
DIRS=$(OS) generic crt lwp stubs
LIBDIR=../rump/lib
LIB=$(LIBDIR)/libfranken.a
OBJDIR=../obj/libc

.PHONY:		$(DIRS) clean test

default:	$(DIRS) $(LIB)

$(DIRS):	
		$(MAKE) OS=$(OS) -C $@

$(LIB):		$(DIRS)
		mkdir -p $(OBJDIR)
		ar cr $(LIB) $(OBJDIR)/*.o

test:		default
		$(MAKE) -C $@

clean:		
		for dir in linux netbsd generic crt lwp stubs test; \
		do \
			$(MAKE) -C $$dir OS= clean; \
		done
		rm -f $(LIB)
