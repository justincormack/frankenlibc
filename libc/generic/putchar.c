#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* XXX add buffering. Will need an isatty ioctl */

int
putchar(int c)
{
	char ch = (char) c;
	int ret __attribute__ ((unused));

	ret = write(1, &ch, 1);		
}
