#include <sys/types.h>

int filter_init(char *);
int filter_fd(int, int, mode_t);
int filter_load_exec(char *, char **, char **);
