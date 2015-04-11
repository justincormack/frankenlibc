#include <sys/types.h>

int filter_init(char *);
int filter_fd(int, int, mode_t);
int filter_load_exec(char *, char **, char **);

int colon_open(char *, char *);
int os_open(char *, char *);
