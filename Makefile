default:	
		./build.sh

seccomp:
		./build.sh seccomp

qemu-arm:
		./build.sh qemu-arm

PHONY:		clean distclean qemu-arm seccomp

clean:		
		rm -rf rumpobj

distclean:	clean
		rm -rf rump
