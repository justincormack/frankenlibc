#include <elf.h>
#include <stdint.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "linux.h"
#include "syscall.h"
#include "init.h"

/* move to a header somewhere */
int __franken_start_main(int (*)(int,char **,char **), int, char **, char **);

int __libc_start_main(int (*)(int,char **,char **), int, char **);

#define AUX_CNT 38

size_t *__auxv;
size_t __hwcap;
size_t __sysinfo;
size_t __pagesize;
size_t __random;

int __platform_random_fd = -1;
int __platform_socket_fd = -1;
int __platform_npoll = 0;
struct pollfd __platform_pollfd[MAXFD];

int __platform_set_thread_area(void *);
static int64_t builtin_tls[4096/sizeof(int64_t)];

int
__libc_start_main(int (*main)(int,char **,char **), int argc, char **argv)
{
	char **envp = argv + argc + 1;
        size_t i, *auxv, aux[AUX_CNT] = { 0 };
	int fd, ret;
	struct linux_stat lst;
	struct ifreq ifr;

        for (i = 0; envp[i]; i++);
        auxv = (void *)(envp + i + 1);
        for (i = 0; auxv[i]; i += 2)
		if (auxv[i] < AUX_CNT)
			aux[auxv[i]] = auxv[i + 1];
	__auxv = auxv;
	__hwcap = aux[AT_HWCAP];
	__sysinfo = aux[AT_SYSINFO];
	__pagesize = aux[AT_PAGESZ];
	__random = aux[AT_RANDOM];

	/* init tls; gcc needs this even for some non-tls using programs */
	__platform_set_thread_area(builtin_tls);

	/* iterate over fds to pick up the special ones */
	for (fd = 0; fd < MAXFD; fd++) {
		if (syscall(SYS_fstat, fd, &lst) == -1)
			break;
		switch (lst.st_mode & LINUX_S_IFMT) {
		case LINUX_S_IFSOCK:
			__platform_socket_fd = fd;
			break;
		case LINUX_S_IFCHR:
			/* /dev/urandom */
			if (lst.st_rdev == makedev(1, 9)) {
				__platform_random_fd = fd;
				break;
			}
			/* macvtap has a dynamic major number, so hard to test */
			if (lst.st_rdev != makedev(10, 200) && major(lst.st_rdev) < 128)
				break;
			ret = syscall(SYS_ioctl, fd, TUNGETIFF, &ifr);
			if (ret == 0) {
				/* we do not yet support macvtap offload facilities */
				if (ifr.ifr_flags & IFF_VNET_HDR) {
					ifr.ifr_flags &= ~IFF_VNET_HDR;
					syscall(SYS_ioctl, fd, TUNSETIFF, &ifr);
				}
				__platform_pollfd[__platform_npoll].fd = fd;
				__platform_pollfd[__platform_npoll].events = POLLIN | POLLPRI;
				__platform_npoll++;
			}
			break;
		}
	}
	return __franken_start_main(main, argc, argv, envp);
}
