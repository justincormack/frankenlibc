#include <unistd.h>

void
_exit(int status)
{
	char die[] = "Terminating\n";

	write(1, die, sizeof(die));
	while (1) {};
}
