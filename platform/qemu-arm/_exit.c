#include <unistd.h>

void
_exit(int status)
{

	/* XXX does not return status */
	__asm__ __volatile__ ("mov r0, #0x18;\nmov r1, %0\nsvc 0x00123456;\n"::"r"(status):"r0", "r1");
}
