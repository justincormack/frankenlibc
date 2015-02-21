#include <stdio.h>
#include <stdlib.h>

ssize_t write(int, const void *, size_t);

int
putchar(int c)
{
	char ch = (char) c;
	int ret __attribute__ ((unused));

	ret = write(1, &ch, 1);		
}
