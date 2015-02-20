#include <errno.h>

int *
__errno(void)
{

	return &errno;
}
