#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFSIZE 4096

int
main(int argc, char **argv)
{
	char buf[BUFSIZE];
	int ret;
	int fd = 0, last;

	last = open("/dev/null", O_RDONLY);
	if (last == -1) {
		perror("open /dev/null");
		return 1;
	}
	close(last);

	while (1) {
		if (fd == 1 || fd == 2) {
			fd++;
			continue;
		}
		if (fd >= last)
			break;
		ret = read(fd, buf, BUFSIZE);
		if (ret == -1) {
			fd++;
			continue;
		}
		if (ret == 0) {
			fd++;
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
