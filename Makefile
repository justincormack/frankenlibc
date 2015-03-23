default:	
		./buildc.sh

test:
		${MAKE} OS=${OS} -C libc test
		${MAKE} -C tests

PHONY:		clean test
clean:		
		rm -rf rumpobj rump
