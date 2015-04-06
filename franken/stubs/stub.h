#include <errno.h>

#define NOTHING(name) \
int name(void); \
int name(void) {return 0;}

#define NOTSUP(name) \
int name(void); \
int name(void) {errno = ENOTSUP; return -1;}
