default:	
		./buildc.sh

test:
		${MAKE} -C tests

seccomp:
		./buildc.sh seccomp

qemu-arm:
		./buildc.sh qemu-arm

PHONY:		clean test qemu-arm seccomp

clean:		
		rm -rf rumpobj rump
