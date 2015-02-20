OS=linux
DIRS=$(OS) generic crt
LIB=../lib/libc.a
OBJDIR=../obj/libc

.PHONY:		$(DIRS) clean

default:	$(DIRS) $(LIB)

$(DIRS):	
		$(MAKE) -C $@

$(LIB):		$(DIRS)
		mkdir -p $(OBJDIR)
		ar cr $(LIB) $(OBJDIR)/*.o

clean:		
		for dir in $(DIRS); do \
			$(MAKE) -C $$dir clean; \
		done
		rm -f $(LIB)
