OS?=linux

default:	
		./buildc.sh

test:
		${MAKE} OS=${OS} -C libc test
		${MAKE} -C tests test

PHONY:		clean test
clean:		
		rm -rf rumpobj rump
