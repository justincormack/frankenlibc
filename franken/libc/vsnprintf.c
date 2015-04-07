#include <stdarg.h>
#include <string.h>

int
vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
	const char *msg = "vsnprintf not implemented\n";

	strncpy(str, msg, size);

	return strlen(msg) + 1 < size ? strlen(msg) + 1 : size;
}
