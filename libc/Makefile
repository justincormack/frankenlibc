OS?=linux
DIRS=$(OS) generic crt lwp stubs
LIB=../lib/libfranken.a
OBJDIR=../obj/libc

.PHONY:		$(DIRS) clean

default:	$(DIRS) $(LIB)

$(DIRS):	
		$(MAKE) OS=$(OS) -C $@

$(LIB):		$(DIRS)
		mkdir -p $(OBJDIR)
		ar cr $(LIB) $(OBJDIR)/*.o

clean:		
		for dir in linux netbsd generic crt lwp stubs; do \
			$(MAKE) -C $$dir OS= clean; \
		done
		rm -f $(LIB)
