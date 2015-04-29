#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define BUFSIZE 4096

int
main(int argc, char **argv)
{
	char buf[BUFSIZE];
	int ret;
	int fd = 3;

	while (1) {
		ret = read(fd, buf, BUFSIZE);
		if (ret == -1) {
			break;
		}
		if (ret == 0) {
			fd++;
			if (fd == 1)
				fd = 3;
			continue;
		}
		ret = write(1, buf, ret);
		if (ret == -1) {
			perror("write");
			return 1;
		}
	}

	return 0;
}
