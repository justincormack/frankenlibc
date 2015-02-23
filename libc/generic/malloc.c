#include <stdlib.h>

void *
malloc(size_t size)
{

	return aligned_alloc(0, size);
}
