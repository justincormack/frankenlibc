/* only used for tests which link against the stub libc in this
   directory and this stub rump kernel */

#include <sys/types.h>

void rump_boot_setsigmodel(int);
int rump_init(void);
int rump_pub_lwproc_rfork(int);
void rump_pub_lwproc_releaselwp(void);
int rump___sysimpl___sysctl(const int *, unsigned int, void *, size_t *, const void *, size_t);

void rump_boot_setsigmodel(int m) {}
int rump_init() {return 0;}
int rump_pub_lwproc_rfork(int f) {return 0;}
void rump_pub_lwproc_releaselwp() {}
int rump___sysimpl___sysctl(const int *name, unsigned int namelen,
	void *oldp, size_t *oldlenp, const void *newp, size_t newlen) {return 0;}
