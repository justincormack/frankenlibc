OS=linux
DIRS=$(OS) generic crt

.PHONY:		$(DIRS) clean

default:	$(DIRS)

$(DIRS):	
		$(MAKE) -C $@
		
clean:		
		for dir in $(DIRS); do \
			$(MAKE) -C $$dir clean; \
		done
