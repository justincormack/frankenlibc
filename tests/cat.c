#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define BUFSIZE 4096

int
main(int argc, char **argv)
{
	char buf[BUFSIZE];
	int ret;

	while (1) {
		ret = read(3, buf, BUFSIZE);
		if (ret == -1) {
			perror("read");
			return 1;
		}
		if (ret == 0) {
			fprintf(stderr, "EOF\n");
			break;
		}
		ret = write(1, buf, ret);
		if (ret == -1) {
			perror("write");
			return 1;
		}
	}

	return 0;
}
