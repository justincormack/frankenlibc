#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
putchar(int c)
{
	char ch = (char) c;
	int ret __attribute__ ((unused));

	ret = write(1, &ch, 1);		
}
