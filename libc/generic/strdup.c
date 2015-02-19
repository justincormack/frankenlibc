#include <string.h>

char *
strdup(const char *s)
{
	size_t len = strlen(s) + 1;
	char *str = malloc(len);

        if (!str)
                return NULL;
        strcpy(str, s);

        return str;
}

