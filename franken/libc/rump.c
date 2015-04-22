/* only used for tests which link against the stub libc in this
   directory and this stub rump kernel */

#include <sys/types.h>

enum rump_etfs_type {
	RUMP_ETFS_REG,
	RUMP_ETFS_BLK,
	RUMP_ETFS_CHR,
	RUMP_ETFS_DIR,
	RUMP_ETFS_DIR_SUBDIRS
};

void rump_boot_setsigmodel(int);
int rump_init(void);
int rump_pub_lwproc_rfork(int);
void rump_pub_lwproc_releaselwp(void);
int rump___sysimpl___sysctl(const int *, unsigned int, void *, size_t *, const void *, size_t);
int rump_pub_etfs_register(const char *, const char *, enum rump_etfs_type);
int rump_pub_netconfig_ifcreate(const char *);
int rump_pub_netconfig_dhcp_ipv4_oneshot(const char *);

void rump_boot_setsigmodel(int m) {}
int rump_init() {return 0;}
int rump_pub_lwproc_rfork(int f) {return 0;}
void rump_pub_lwproc_releaselwp() {}
int rump___sysimpl___sysctl(const int *name, unsigned int namelen,
	void *oldp, size_t *oldlenp, const void *newp, size_t newlen) {return 0;}

int rump_pub_etfs_register(const char *key, const char *hostpath, enum rump_etfs_type ftype)
{return 0;}
int rump_pub_netconfig_ifcreate(const char *key) {return 0;}
int rump_pub_netconfig_dhcp_ipv4_oneshot(const char *key) {return 0;}
