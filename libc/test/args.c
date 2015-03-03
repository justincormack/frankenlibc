#include <string.h>
#include <assert.h>

int
main(int argc, char **argv)
{

	assert(argc == 3);
	assert(strcmp(argv[1], "franken") == 0);
	assert(strcmp(argv[2], "rump") == 0);

	return 0;
}
