default:	
		./buildc.sh

seccomp:
		./buildc.sh seccomp

qemu-arm:
		./buildc.sh qemu-arm

PHONY:		clean distclean qemu-arm seccomp

clean:		
		rm -rf rumpobj

distclean:	clean
		rm -rf rump
