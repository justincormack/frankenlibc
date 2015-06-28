#include <unistd.h>

ssize_t
write(int fd, const void *buf, size_t count)
{
	const char *cbuf = buf;
	int i;

	for (i = 0; i < count; i++)
		__asm__ __volatile__ ("mov r0, #0x03;\nmov r1, %0\nsvc 0x00123456;\n"::"r"(&cbuf[i]):"r0", "r1");

	return count;
}
