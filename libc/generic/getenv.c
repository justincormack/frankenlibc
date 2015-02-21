#include <errno.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

/* TODO once we set up initialization */

char *
getenv(const char *name)
{
	size_t len = strlen(name);
	char **p;

	if (strchr(name, '=') != NULL) { /* XXX not required in the standard */
		errno = EINVAL;
		return NULL;
	}
	for (p = environ; *p != NULL; p++) {
		if (strncmp(*p, name, len) != 0 || (*p)[len] != '=')
			continue;
		return &((*p)[len+1]);
	}

	return NULL;
}
