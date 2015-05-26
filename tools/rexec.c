#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "rexec.h"

extern char **environ;

static void
usage(char *name)
{

	printf("Usage: %s program [-ro|-rw] [files] [-- args]\n", name);
	exit(1);
}

struct fdinfo {
	int fd;
	int flags;
	mode_t mode;
};

int
main(int argc, char **argv)
{
	int i, p = 0;
	int fd;
	char *program = NULL;
	char *pargs[argc];
	int mode = O_RDWR;
	int ret;
	int fl;
	struct timespec ts;
	struct fdinfo *fds;
	int nfds = 3;
	struct stat st;
	char *path;
	char prog[4096];

	if (argc < 2)
		usage(argv[0]);

	for (i = 1; i < argc; i++) {
		char *arg = argv[i];

		if (strcmp(arg, "-h") == 0)
			usage(argv[0]);
		if (i == 1) {
			program = arg;
			pargs[p++] = program;
			continue;
		}
		if (strcmp(arg, "-ro") == 0) {
			mode = O_RDONLY;
			continue;
		}
		if (strcmp(arg, "-rw") == 0) {
			mode = O_RDWR;
			continue;
		}
		if (strcmp(arg, "-noroot") == 0) {
			fd = open("/dev/null", O_RDONLY);
			if (fd == -1) {
				perror("open /dev/null");
				exit(1);
			}
			if (fd != 3) {
				fprintf(stderr, "-noroot must be specified before any file opened\n");
				exit(1);
			}
			continue;
		}
		if (strcmp(arg, "--") == 0) {
			i++;
			break;			
		}
		if (strchr(arg, ':')) {
			char *colon = strchr(arg, ':');
			char *pre;

			pre = strndup(arg, colon - arg);
			fd = colon_open(pre, &colon[1]);
			free(pre);
			if (fd == -1)
				continue;
		} else {
			fd = open(arg, mode);
			if (fd == -1) {
				perror("open");
				exit(1);
			}
			fl = fcntl(fd, F_GETFL);
			if (fl == -1) {
				perror("fcntl");
				exit(1);
			}
			ret = fcntl(fd, F_SETFL, fl | O_NONBLOCK);
			if (ret == -1) {
				perror("fcntl");
				exit(1);
			}
		}
	}

	for (; i < argc; i++)
		pargs[p++] = argv[i];

	pargs[p] = "\0";

	for (; p < argc; p++)
		pargs[p] = 0;

	os_post();

	nfds = open("/dev/null", O_RDONLY);
	close(nfds);

	if (strchr(program, '/') == NULL) {
		char *part;

		/* only name specified, look in PATH */
		path = getenv("PATH");
		if (! path) {
			fprintf(stderr, "no PATH set\n");
			exit(1);
		}
		path = strdup(path);
		part = strtok(path, ":");
		while (part) {
			if (strlen(part) + 1 + strlen(program) < sizeof(prog)) {
				strncpy(prog, part, sizeof(prog));
				strncat(prog, "/", 1);
				strncat(prog, program, strlen(program));
				if (access(prog, R_OK | X_OK) == 0)
					break;
			}
			part = strtok(NULL, ":");
		}
		free(path);
		if (! part) {
			fprintf(stderr, "Could not find %s in PATH\n", program);
			exit(1);
		}
		program = prog;
	}

	ret = filter_init(program);
	if (ret < 0) {
		fprintf(stderr, "filter_init failed\n");
		exit(1);
	}

	for (fd = 0; fd < nfds; fd++) {
		fl = fcntl(fd, F_GETFL);
		if (fl == -1) {
			perror("fcntl");
			exit(1);
		}
		ret = fstat(fd, &st);
		if (ret == -1) {
			perror("fstat");
			exit(1);
		}
		ret = filter_fd(fd, fl, &st);
		if (ret < 0) {
			fprintf(stderr, "filter_fd failed\n");
			exit(1);
		}
	}

	ret = filter_load_exec(program, pargs, environ);
	if (ret < 0) {
		fprintf(stderr, "filter_load_exec failed\n");
		exit(1);
	}

	return 0;	
}

int
colon_open(char *pre, char *post)
{
	int fd, ret;

	/* open file as console for writing, use /dev/null as input */
	if (strcmp(pre, "console") == 0) {
		fd = open(post, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
		if (fd == -1) {
			perror("console open");
			exit(1);
		}
		ret = dup2(fd, 1);
		if (ret == -1) {
			perror("dup2");
			exit(1);
		}
		ret = dup2(fd, 2);
		if (ret == -1) {
			perror("dup2");
			exit(1);
		}
		close(fd);
		fd = open("/dev/null", O_RDONLY);
		if (ret == -1) {
			perror("open /dev/null");
			exit(1);
		}
		ret = dup2(fd, 0);
		if (ret == -1) {
			perror("dup2");
			exit(1);
		}
		close(fd);
		return -1;
	}

	return os_open(pre, post);
}

/* create an empty working directory, chroot if able */
int
emptydir()
{
	char template[20] = "/tmp/dirXXXXXX";
	char *dir;
	int ret;
	int dirfd;

	dirfd = open(".", O_RDONLY|O_DIRECTORY);
	if (dirfd == -1) {
		perror("open");
		return 1;
	}

	dir = mkdtemp(template);
	if (! dir) {
		perror("mkdtemp");
		return 1;
	}

	if (chdir(dir) == -1) {
		perror("chdir");
		return 1;
	}

#ifdef AT_REMOVEDIR
	if (unlinkat(dirfd, dir, AT_REMOVEDIR) == -1) {
		perror("unlinkat");
		return 1;
	}
#endif

	if (close(dirfd) == -1) {
		perror("close");
		return 1;
	}

	if (chroot(".") == 0) {
		if (chdir("/") == -1) {
			perror("chdir");
			return 1;
		}
		if (chmod(".", 0) == -1) {
			perror("chmod");
			return -1;
		}
	}

	return 0;	
}
