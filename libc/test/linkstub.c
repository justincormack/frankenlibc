#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

char *environ = NULL;
void rump_boot_setsigmodel(int);
void rump_init(void);
void _libc_init(void);

void rump_boot_setsigmodel(int p) {};
void rump_init(void) {};
void _libc_init(void) {};
void exit(int v) {_exit(v);}
