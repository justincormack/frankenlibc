BINDIR=../rump/bin
OUT=$(BINDIR)/rumprun

default:		$(OUT)

$(BINDIR)/rumprun:	rumprun.c
			$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ rumprun.c

.PHONY:			clean
clean:		
			rm -f $(OUT)
