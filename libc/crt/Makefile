ARCH=x86_64
OS=linux
CSRC=crti.c crtn.c
COBJ=$(CSRC:.c=.o)
ASRC=$(OS)/$(ARCH)/crt1.s
AOBJ=$(ASRC:.s=.o)
OBJ=$(AOBJ) $(COBJ)
CPPFLAGS+=-nostdinc
CFLAGS+=-fno-stack-protector

default:	$(OBJ)

crti.o:		crti.c

crtn.o:		crtn.c

crt1.o:		$(OS)/$(ARCH)/crt1.s

.PHONY:		clean
clean:		
		rm -f *.o
