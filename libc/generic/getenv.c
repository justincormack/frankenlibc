#include <stdlib.h>
#include <string.h>

/* TODO once we set up initialization */

char *
getenv(const char *name)
{

	/* temp hack XXX */
	if (strcmp(name, "RUMP_VERBOSE") == 0)
		return "1";
	return NULL;
}
