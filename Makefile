default:	
		./build.sh

seccomp:
		./build.sh seccomp

qemu-arm:
		./build.sh qemu-arm

pk:
		./build.sh pk

PHONY:		clean distclean qemu-arm pk seccomp

clean:		
		rm -rf rumpobj

distclean:	clean
		rm -rf rump
