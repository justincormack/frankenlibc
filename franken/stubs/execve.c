#include <errno.h>

int execve(const char *, char *const [], char *const []);

int
execve(const char *path, char *const argv[], char *const envp[])
{

	errno = ENOTSUP;
	return -1;
}
