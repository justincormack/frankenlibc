default:	
		./buildc.sh

test:
		${MAKE} -C tests

PHONY:		clean test
clean:		
		rm -rf rumpobj rump
