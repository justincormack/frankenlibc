#include <unistd.h>

volatile unsigned int *const UART0DR = (unsigned int *)0x101f1000;

ssize_t
write(int fd, const void *buf, size_t count)
{
	const char *cbuf = buf;
	int i;

	for (i = 0; i < count; i++)
		*UART0DR = (unsigned int)(cbuf[i]);

	return count;
}
