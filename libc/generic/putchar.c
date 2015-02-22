#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* XXX add buffering */

static int initialized = 0;

int
putchar(int c)
{
	char ch = (char) c;
	int ret __attribute__ ((unused));

	if (! initialized) {
		ret = isatty(1); /* XXX set line buffering if so */
		initialized = 1;
	}

	ret = write(1, &ch, 1);		
}
