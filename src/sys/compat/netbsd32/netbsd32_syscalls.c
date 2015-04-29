/* $NetBSD: netbsd32_syscalls.c,v 1.110 2015/03/07 16:41:53 christos Exp $ */

/*
 * System call names.
 *
 * DO NOT EDIT-- this file is automatically generated.
 * created from	NetBSD: syscalls.master,v 1.102 2015/02/25 13:16:33 christos Exp
 */

#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD: netbsd32_syscalls.c,v 1.110 2015/03/07 16:41:53 christos Exp $");

#if defined(_KERNEL_OPT)
#if defined(_KERNEL_OPT)
#include "opt_compat_netbsd.h"
#include "opt_ntp.h"
#include "opt_sysv.h"
#include "opt_compat_43.h"
#endif
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/signal.h>
#include <sys/mount.h>
#include <sys/syscallargs.h>
#include <compat/netbsd32/netbsd32.h>
#include <compat/netbsd32/netbsd32_syscallargs.h>
#endif /* _KERNEL_OPT */

const char *const netbsd32_syscallnames[] = {
	/*   0 */	"netbsd32_syscall",
	/*   1 */	"netbsd32_exit",
	/*   2 */	"fork",
	/*   3 */	"netbsd32_read",
	/*   4 */	"netbsd32_write",
	/*   5 */	"netbsd32_open",
	/*   6 */	"netbsd32_close",
	/*   7 */	"compat_50_netbsd32_wait4",
	/*   8 */	"compat_43_netbsd32_ocreat",
	/*   9 */	"netbsd32_link",
	/*  10 */	"netbsd32_unlink",
	/*  11 */	"#11 (obsolete execv)",
	/*  12 */	"netbsd32_chdir",
	/*  13 */	"netbsd32_fchdir",
	/*  14 */	"compat_50_netbsd32_mknod",
	/*  15 */	"netbsd32_chmod",
	/*  16 */	"netbsd32_chown",
	/*  17 */	"netbsd32_break",
	/*  18 */	"compat_20_netbsd32_getfsstat",
	/*  19 */	"compat_43_netbsd32_olseek",
	/*  20 */	"getpid",
	/*  21 */	"netbsd32_mount",
	/*  22 */	"netbsd32_unmount",
	/*  23 */	"netbsd32_setuid",
	/*  24 */	"getuid",
	/*  25 */	"geteuid",
	/*  26 */	"netbsd32_ptrace",
	/*  27 */	"netbsd32_recvmsg",
	/*  28 */	"netbsd32_sendmsg",
	/*  29 */	"netbsd32_recvfrom",
	/*  30 */	"netbsd32_accept",
	/*  31 */	"netbsd32_getpeername",
	/*  32 */	"netbsd32_getsockname",
	/*  33 */	"netbsd32_access",
	/*  34 */	"netbsd32_chflags",
	/*  35 */	"netbsd32_fchflags",
	/*  36 */	"sync",
	/*  37 */	"netbsd32_kill",
	/*  38 */	"compat_43_netbsd32_stat43",
	/*  39 */	"getppid",
	/*  40 */	"compat_43_netbsd32_lstat43",
	/*  41 */	"netbsd32_dup",
	/*  42 */	"pipe",
	/*  43 */	"getegid",
	/*  44 */	"netbsd32_profil",
	/*  45 */	"netbsd32_ktrace",
	/*  46 */	"netbsd32_sigaction",
	/*  47 */	"getgid",
	/*  48 */	"compat_13_sigprocmask13",
	/*  49 */	"netbsd32___getlogin",
	/*  50 */	"netbsd32_setlogin",
	/*  51 */	"netbsd32_acct",
	/*  52 */	"compat_13_sigpending13",
	/*  53 */	"compat_13_netbsd32_sigaltstack13",
	/*  54 */	"netbsd32_ioctl",
	/*  55 */	"compat_12_netbsd32_reboot",
	/*  56 */	"netbsd32_revoke",
	/*  57 */	"netbsd32_symlink",
	/*  58 */	"netbsd32_readlink",
	/*  59 */	"netbsd32_execve",
	/*  60 */	"netbsd32_umask",
	/*  61 */	"netbsd32_chroot",
	/*  62 */	"compat_43_netbsd32_fstat43",
	/*  63 */	"compat_43_netbsd32_ogetkerninfo",
	/*  64 */	"compat_43_ogetpagesize",
	/*  65 */	"compat_12_netbsd32_msync",
	/*  66 */	"vfork",
	/*  67 */	"#67 (obsolete vread)",
	/*  68 */	"#68 (obsolete vwrite)",
	/*  69 */	"netbsd32_sbrk",
	/*  70 */	"netbsd32_sstk",
	/*  71 */	"compat_43_netbsd32_ommap",
	/*  72 */	"vadvise",
	/*  73 */	"netbsd32_munmap",
	/*  74 */	"netbsd32_mprotect",
	/*  75 */	"netbsd32_madvise",
	/*  76 */	"#76 (obsolete vhangup)",
	/*  77 */	"#77 (obsolete vlimit)",
	/*  78 */	"netbsd32_mincore",
	/*  79 */	"netbsd32_getgroups",
	/*  80 */	"netbsd32_setgroups",
	/*  81 */	"getpgrp",
	/*  82 */	"netbsd32_setpgid",
	/*  83 */	"compat_50_netbsd32_setitimer",
	/*  84 */	"compat_43_owait",
	/*  85 */	"compat_12_netbsd32_oswapon",
	/*  86 */	"compat_50_netbsd32_getitimer",
	/*  87 */	"compat_43_netbsd32_ogethostname",
	/*  88 */	"compat_43_netbsd32_osethostname",
	/*  89 */	"compat_43_ogetdtablesize",
	/*  90 */	"netbsd32_dup2",
	/*  91 */	"#91 (unimplemented getdopt)",
	/*  92 */	"netbsd32_fcntl",
	/*  93 */	"compat_50_netbsd32_select",
	/*  94 */	"#94 (unimplemented setdopt)",
	/*  95 */	"netbsd32_fsync",
	/*  96 */	"netbsd32_setpriority",
	/*  97 */	"compat_30_netbsd32_socket",
	/*  98 */	"netbsd32_connect",
	/*  99 */	"compat_43_netbsd32_oaccept",
	/* 100 */	"netbsd32_getpriority",
	/* 101 */	"compat_43_netbsd32_osend",
	/* 102 */	"compat_43_netbsd32_orecv",
	/* 103 */	"compat_13_sigreturn13",
	/* 104 */	"netbsd32_bind",
	/* 105 */	"netbsd32_setsockopt",
	/* 106 */	"netbsd32_listen",
	/* 107 */	"#107 (obsolete vtimes)",
	/* 108 */	"compat_43_netbsd32_osigvec",
	/* 109 */	"compat_43_netbsd32_sigblock",
	/* 110 */	"compat_43_netbsd32_sigsetmask",
	/* 111 */	"compat_13_sigsuspend13",
	/* 112 */	"compat_43_netbsd32_osigstack",
	/* 113 */	"compat_43_netbsd32_orecvmsg",
	/* 114 */	"compat_43_netbsd32_osendmsg",
	/* 115 */	"#115 (obsolete vtrace)",
	/* 116 */	"compat_50_netbsd32_gettimeofday",
	/* 117 */	"compat_50_netbsd32_getrusage",
	/* 118 */	"netbsd32_getsockopt",
	/* 119 */	"#119 (obsolete resuba)",
	/* 120 */	"netbsd32_readv",
	/* 121 */	"netbsd32_writev",
	/* 122 */	"compat_50_netbsd32_settimeofday",
	/* 123 */	"netbsd32_fchown",
	/* 124 */	"netbsd32_fchmod",
	/* 125 */	"compat_43_netbsd32_orecvfrom",
	/* 126 */	"netbsd32_setreuid",
	/* 127 */	"netbsd32_setregid",
	/* 128 */	"netbsd32_rename",
	/* 129 */	"compat_43_netbsd32_otruncate",
	/* 130 */	"compat_43_netbsd32_oftruncate",
	/* 131 */	"netbsd32_flock",
	/* 132 */	"netbsd32_mkfifo",
	/* 133 */	"netbsd32_sendto",
	/* 134 */	"netbsd32_shutdown",
	/* 135 */	"netbsd32_socketpair",
	/* 136 */	"netbsd32_mkdir",
	/* 137 */	"netbsd32_rmdir",
	/* 138 */	"compat_50_netbsd32_utimes",
	/* 139 */	"#139 (obsolete 4.2 sigreturn)",
	/* 140 */	"compat_50_netbsd32_adjtime",
	/* 141 */	"compat_43_netbsd32_ogetpeername",
	/* 142 */	"compat_43_ogethostid",
	/* 143 */	"compat_43_netbsd32_sethostid",
	/* 144 */	"compat_43_netbsd32_ogetrlimit",
	/* 145 */	"compat_43_netbsd32_osetrlimit",
	/* 146 */	"compat_43_netbsd32_killpg",
	/* 147 */	"setsid",
	/* 148 */	"compat_50_netbsd32_quotactl",
	/* 149 */	"compat_43_oquota",
	/* 150 */	"compat_43_netbsd32_ogetsockname",
	/* 151 */	"#151 (unimplemented)",
	/* 152 */	"#152 (unimplemented)",
	/* 153 */	"#153 (unimplemented)",
	/* 154 */	"#154 (unimplemented)",
	/* 155 */	"#155 (unimplemented netbsd32_nfssvc)",
	/* 156 */	"compat_43_netbsd32_ogetdirentries",
	/* 157 */	"compat_20_netbsd32_statfs",
	/* 158 */	"compat_20_netbsd32_fstatfs",
	/* 159 */	"#159 (unimplemented)",
	/* 160 */	"#160 (unimplemented)",
	/* 161 */	"compat_30_netbsd32_getfh",
	/* 162 */	"compat_09_netbsd32_ogetdomainname",
	/* 163 */	"compat_09_netbsd32_osetdomainname",
	/* 164 */	"compat_09_netbsd32_uname",
	/* 165 */	"netbsd32_sysarch",
	/* 166 */	"#166 (unimplemented)",
	/* 167 */	"#167 (unimplemented)",
	/* 168 */	"#168 (unimplemented)",
#if defined(SYSVSEM) || !defined(_KERNEL_OPT)
	/* 169 */	"compat_10_osemsys",
#else
	/* 169 */	"#169 (excluded netbsd32_semsys)",
#endif
#if defined(SYSVMSG) || !defined(_KERNEL_OPT)
	/* 170 */	"compat_10_omsgsys",
#else
	/* 170 */	"#170 (excluded netbsd32_msgsys)",
#endif
#if defined(SYSVSHM) || !defined(_KERNEL_OPT)
	/* 171 */	"compat_10_oshmsys",
#else
	/* 171 */	"#171 (excluded netbsd32_shmsys)",
#endif
	/* 172 */	"#172 (unimplemented)",
	/* 173 */	"netbsd32_pread",
	/* 174 */	"netbsd32_pwrite",
#if defined(NTP) || !defined(_KERNEL_OPT)
	/* 175 */	"compat_30_netbsd32_ntp_gettime",
	/* 176 */	"netbsd32_ntp_adjtime",
#else
	/* 175 */	"#175 (excluded ntp_gettime)",
	/* 176 */	"#176 (excluded ntp_adjtime)",
#endif
	/* 177 */	"#177 (unimplemented)",
	/* 178 */	"#178 (unimplemented)",
	/* 179 */	"#179 (unimplemented)",
	/* 180 */	"#180 (unimplemented)",
	/* 181 */	"netbsd32_setgid",
	/* 182 */	"netbsd32_setegid",
	/* 183 */	"netbsd32_seteuid",
	/* 184 */	"#184 (excluded netbsd32_lfs_bmapv)",
	/* 185 */	"#185 (excluded netbsd32_lfs_markv)",
	/* 186 */	"#186 (excluded netbsd32_lfs_segclean)",
	/* 187 */	"#187 (excluded netbsd32_lfs_segwait)",
	/* 188 */	"compat_12_netbsd32_stat12",
	/* 189 */	"compat_12_netbsd32_fstat12",
	/* 190 */	"compat_12_netbsd32_lstat12",
	/* 191 */	"netbsd32_pathconf",
	/* 192 */	"netbsd32_fpathconf",
	/* 193 */	"#193 (unimplemented)",
	/* 194 */	"netbsd32_getrlimit",
	/* 195 */	"netbsd32_setrlimit",
	/* 196 */	"compat_12_netbsd32_getdirentries",
	/* 197 */	"netbsd32_mmap",
	/* 198 */	"netbsd32____syscall",
	/* 199 */	"netbsd32_lseek",
	/* 200 */	"netbsd32_truncate",
	/* 201 */	"netbsd32_ftruncate",
	/* 202 */	"netbsd32___sysctl",
	/* 203 */	"netbsd32_mlock",
	/* 204 */	"netbsd32_munlock",
	/* 205 */	"netbsd32_undelete",
	/* 206 */	"compat_50_netbsd32_futimes",
	/* 207 */	"netbsd32_getpgid",
	/* 208 */	"netbsd32_reboot",
	/* 209 */	"netbsd32_poll",
	/* 210 */	"#210 (unimplemented)",
	/* 211 */	"#211 (unimplemented)",
	/* 212 */	"#212 (unimplemented)",
	/* 213 */	"#213 (unimplemented)",
	/* 214 */	"#214 (unimplemented)",
	/* 215 */	"#215 (unimplemented)",
	/* 216 */	"#216 (unimplemented)",
	/* 217 */	"#217 (unimplemented)",
	/* 218 */	"#218 (unimplemented)",
	/* 219 */	"#219 (unimplemented)",
#if defined(SYSVSEM) || !defined(_KERNEL_OPT)
	/* 220 */	"compat_14_netbsd32___semctl",
	/* 221 */	"netbsd32_semget",
	/* 222 */	"netbsd32_semop",
	/* 223 */	"netbsd32_semconfig",
#else
	/* 220 */	"#220 (excluded compat_14_netbsd32_semctl)",
	/* 221 */	"#221 (excluded netbsd32_semget)",
	/* 222 */	"#222 (excluded netbsd32_semop)",
	/* 223 */	"#223 (excluded netbsd32_semconfig)",
#endif
#if defined(SYSVMSG) || !defined(_KERNEL_OPT)
	/* 224 */	"compat_14_netbsd32_msgctl",
	/* 225 */	"netbsd32_msgget",
	/* 226 */	"netbsd32_msgsnd",
	/* 227 */	"netbsd32_msgrcv",
#else
	/* 224 */	"#224 (excluded compat_14_netbsd32_msgctl)",
	/* 225 */	"#225 (excluded netbsd32_msgget)",
	/* 226 */	"#226 (excluded netbsd32_msgsnd)",
	/* 227 */	"#227 (excluded netbsd32_msgrcv)",
#endif
#if defined(SYSVSHM) || !defined(_KERNEL_OPT)
	/* 228 */	"netbsd32_shmat",
	/* 229 */	"compat_14_netbsd32_shmctl",
	/* 230 */	"netbsd32_shmdt",
	/* 231 */	"netbsd32_shmget",
#else
	/* 228 */	"#228 (excluded netbsd32_shmat)",
	/* 229 */	"#229 (excluded compat_14_netbsd32_shmctl)",
	/* 230 */	"#230 (excluded netbsd32_shmdt)",
	/* 231 */	"#231 (excluded netbsd32_shmget)",
#endif
	/* 232 */	"compat_50_netbsd32_clock_gettime",
	/* 233 */	"compat_50_netbsd32_clock_settime",
	/* 234 */	"compat_50_netbsd32_clock_getres",
	/* 235 */	"netbsd32_timer_create",
	/* 236 */	"netbsd32_timer_delete",
	/* 237 */	"compat_50_netbsd32_timer_settime",
	/* 238 */	"compat_50_netbsd32_timer_gettime",
	/* 239 */	"netbsd32_timer_getoverrun",
	/* 240 */	"compat_50_netbsd32_nanosleep",
	/* 241 */	"netbsd32_fdatasync",
	/* 242 */	"netbsd32_mlockall",
	/* 243 */	"munlockall",
	/* 244 */	"compat_50_netbsd32___sigtimedwait",
	/* 245 */	"#245 (unimplemented)",
	/* 246 */	"#246 (unimplemented)",
	/* 247 */	"netbsd32__ksem_init",
	/* 248 */	"netbsd32__ksem_open",
	/* 249 */	"netbsd32__ksem_unlink",
	/* 250 */	"netbsd32__ksem_close",
	/* 251 */	"netbsd32__ksem_post",
	/* 252 */	"netbsd32__ksem_wait",
	/* 253 */	"netbsd32__ksem_trywait",
	/* 254 */	"netbsd32__ksem_getvalue",
	/* 255 */	"netbsd32__ksem_destroy",
	/* 256 */	"netbsd32__ksem_timedwait",
	/* 257 */	"#257 (unimplemented)",
	/* 258 */	"#258 (unimplemented)",
	/* 259 */	"#259 (unimplemented)",
	/* 260 */	"#260 (unimplemented)",
	/* 261 */	"#261 (unimplemented)",
	/* 262 */	"#262 (unimplemented)",
	/* 263 */	"#263 (unimplemented)",
	/* 264 */	"#264 (unimplemented)",
	/* 265 */	"#265 (unimplemented)",
	/* 266 */	"#266 (unimplemented)",
	/* 267 */	"#267 (unimplemented)",
	/* 268 */	"#268 (unimplemented)",
	/* 269 */	"#269 (unimplemented)",
	/* 270 */	"netbsd32___posix_rename",
	/* 271 */	"netbsd32_swapctl",
	/* 272 */	"compat_30_netbsd32_getdents",
	/* 273 */	"netbsd32_minherit",
	/* 274 */	"netbsd32_lchmod",
	/* 275 */	"netbsd32_lchown",
	/* 276 */	"compat_50_netbsd32_lutimes",
	/* 277 */	"netbsd32___msync13",
	/* 278 */	"compat_30_netbsd32___stat13",
	/* 279 */	"compat_30_netbsd32___fstat13",
	/* 280 */	"compat_30_netbsd32___lstat13",
	/* 281 */	"netbsd32___sigaltstack14",
	/* 282 */	"__vfork14",
	/* 283 */	"netbsd32___posix_chown",
	/* 284 */	"netbsd32___posix_fchown",
	/* 285 */	"netbsd32___posix_lchown",
	/* 286 */	"netbsd32_getsid",
	/* 287 */	"netbsd32___clone",
	/* 288 */	"netbsd32_fktrace",
	/* 289 */	"netbsd32_preadv",
	/* 290 */	"netbsd32_pwritev",
	/* 291 */	"netbsd32___sigaction14",
	/* 292 */	"netbsd32___sigpending14",
	/* 293 */	"netbsd32___sigprocmask14",
	/* 294 */	"netbsd32___sigsuspend14",
	/* 295 */	"compat_16_netbsd32___sigreturn14",
	/* 296 */	"netbsd32___getcwd",
	/* 297 */	"netbsd32_fchroot",
	/* 298 */	"compat_30_netbsd32_fhopen",
	/* 299 */	"compat_30_netbsd32_fhstat",
	/* 300 */	"compat_20_netbsd32_fhstatfs",
#if defined(SYSVSEM) || !defined(_KERNEL_OPT)
	/* 301 */	"compat_50_netbsd32___semctl14",
#else
	/* 301 */	"#301 (excluded __semctl14)",
#endif
#if defined(SYSVMSG) || !defined(_KERNEL_OPT)
	/* 302 */	"compat_50_netbsd32___msgctl13",
#else
	/* 302 */	"#302 (excluded __msgctl13)",
#endif
#if defined(SYSVSHM) || !defined(_KERNEL_OPT)
	/* 303 */	"compat_50_netbsd32___shmctl13",
#else
	/* 303 */	"#303 (excluded __shmctl13)",
#endif
	/* 304 */	"netbsd32_lchflags",
	/* 305 */	"issetugid",
	/* 306 */	"netbsd32_utrace",
	/* 307 */	"netbsd32_getcontext",
	/* 308 */	"netbsd32_setcontext",
	/* 309 */	"netbsd32__lwp_create",
	/* 310 */	"_lwp_exit",
	/* 311 */	"_lwp_self",
	/* 312 */	"netbsd32__lwp_wait",
	/* 313 */	"netbsd32__lwp_suspend",
	/* 314 */	"netbsd32__lwp_continue",
	/* 315 */	"netbsd32__lwp_wakeup",
	/* 316 */	"_lwp_getprivate",
	/* 317 */	"netbsd32__lwp_setprivate",
	/* 318 */	"netbsd32__lwp_kill",
	/* 319 */	"netbsd32__lwp_detach",
	/* 320 */	"compat_50_netbsd32__lwp_park",
	/* 321 */	"netbsd32__lwp_unpark",
	/* 322 */	"netbsd32__lwp_unpark_all",
	/* 323 */	"netbsd32__lwp_setname",
	/* 324 */	"netbsd32__lwp_getname",
	/* 325 */	"netbsd32__lwp_ctl",
	/* 326 */	"#326 (unimplemented)",
	/* 327 */	"#327 (unimplemented)",
	/* 328 */	"#328 (unimplemented)",
	/* 329 */	"#329 (unimplemented)",
	/* 330 */	"#330 (obsolete netbsd32_sa_register)",
	/* 331 */	"#331 (obsolete netbsd32_sa_stacks)",
	/* 332 */	"#332 (obsolete sa_enable)",
	/* 333 */	"#333 (obsolete netbsd32_sa_setconcurrency)",
	/* 334 */	"#334 (obsolete sa_yield)",
	/* 335 */	"#335 (obsolete netbsd32_sa_preempt)",
	/* 336 */	"#336 (obsolete sys_sa_unblockyield)",
	/* 337 */	"#337 (unimplemented)",
	/* 338 */	"#338 (unimplemented)",
	/* 339 */	"#339 (unimplemented)",
	/* 340 */	"netbsd32___sigaction_sigtramp",
	/* 341 */	"#341 (unimplemented)",
	/* 342 */	"#342 (unimplemented)",
	/* 343 */	"netbsd32_rasctl",
	/* 344 */	"kqueue",
	/* 345 */	"compat_50_netbsd32_kevent",
	/* 346 */	"netbsd32__sched_setparam",
	/* 347 */	"netbsd32__sched_getparam",
	/* 348 */	"netbsd32__sched_setaffinity",
	/* 349 */	"netbsd32__sched_getaffinity",
	/* 350 */	"sched_yield",
	/* 351 */	"#351 (unimplemented)",
	/* 352 */	"#352 (unimplemented)",
	/* 353 */	"#353 (unimplemented)",
	/* 354 */	"netbsd32_fsync_range",
	/* 355 */	"netbsd32_uuidgen",
	/* 356 */	"netbsd32_getvfsstat",
	/* 357 */	"netbsd32_statvfs1",
	/* 358 */	"netbsd32_fstatvfs1",
	/* 359 */	"compat_30_netbsd32_fhstatvfs1",
	/* 360 */	"netbsd32_extattrctl",
	/* 361 */	"netbsd32_extattr_set_file",
	/* 362 */	"netbsd32_extattr_get_file",
	/* 363 */	"netbsd32_extattr_delete_file",
	/* 364 */	"netbsd32_extattr_set_fd",
	/* 365 */	"netbsd32_extattr_get_fd",
	/* 366 */	"netbsd32_extattr_delete_fd",
	/* 367 */	"netbsd32_extattr_set_link",
	/* 368 */	"netbsd32_extattr_get_link",
	/* 369 */	"netbsd32_extattr_delete_link",
	/* 370 */	"netbsd32_extattr_list_fd",
	/* 371 */	"netbsd32_extattr_list_file",
	/* 372 */	"netbsd32_extattr_list_link",
	/* 373 */	"compat_50_netbsd32_pselect",
	/* 374 */	"compat_50_netbsd32_pollts",
	/* 375 */	"netbsd32_setxattr",
	/* 376 */	"netbsd32_lsetxattr",
	/* 377 */	"netbsd32_fsetxattr",
	/* 378 */	"netbsd32_getxattr",
	/* 379 */	"netbsd32_lgetxattr",
	/* 380 */	"netbsd32_fgetxattr",
	/* 381 */	"netbsd32_listxattr",
	/* 382 */	"netbsd32_llistxattr",
	/* 383 */	"netbsd32_flistxattr",
	/* 384 */	"netbsd32_removexattr",
	/* 385 */	"netbsd32_lremovexattr",
	/* 386 */	"netbsd32_fremovexattr",
	/* 387 */	"compat_50_netbsd32___stat30",
	/* 388 */	"compat_50_netbsd32___fstat30",
	/* 389 */	"compat_50_netbsd32___lstat30",
	/* 390 */	"netbsd32___getdents30",
	/* 391 */	"#391 (ignored old posix fadvise)",
	/* 392 */	"compat_30_netbsd32___fhstat30",
#if defined(NTP) || !defined(_KERNEL_OPT)
	/* 393 */	"compat_50_netbsd32_ntp_gettime",
#else
	/* 393 */	"#393 (excluded __ntp_gettime30)",
#endif
	/* 394 */	"netbsd32___socket30",
	/* 395 */	"netbsd32___getfh30",
	/* 396 */	"netbsd32___fhopen40",
	/* 397 */	"netbsd32___fhstatvfs140",
	/* 398 */	"compat_50_netbsd32___fhstat40",
	/* 399 */	"#399 (unimplemented sys_aio_cancel)",
	/* 400 */	"#400 (unimplemented sys_aio_error)",
	/* 401 */	"#401 (unimplemented sys_aio_fsync)",
	/* 402 */	"#402 (unimplemented sys_aio_read)",
	/* 403 */	"#403 (unimplemented sys_aio_return)",
	/* 404 */	"#404 (unimplemented sys_aio_suspend)",
	/* 405 */	"#405 (unimplemented sys_aio_write)",
	/* 406 */	"#406 (unimplemented sys_lio_listio)",
	/* 407 */	"#407 (unimplemented)",
	/* 408 */	"#408 (unimplemented)",
	/* 409 */	"#409 (unimplemented)",
	/* 410 */	"netbsd32___mount50",
	/* 411 */	"netbsd32_mremap",
	/* 412 */	"#412 (unimplemented)",
	/* 413 */	"#413 (unimplemented)",
	/* 414 */	"#414 (unimplemented)",
	/* 415 */	"#415 (unimplemented)",
	/* 416 */	"netbsd32___posix_fadvise50",
	/* 417 */	"netbsd32___select50",
	/* 418 */	"netbsd32___gettimeofday50",
	/* 419 */	"netbsd32___settimeofday50",
	/* 420 */	"netbsd32___utimes50",
	/* 421 */	"netbsd32___adjtime50",
	/* 422 */	"#422 (excluded __lfs_segwait50)",
	/* 423 */	"netbsd32___futimes50",
	/* 424 */	"netbsd32___lutimes50",
	/* 425 */	"netbsd32___setitimer50",
	/* 426 */	"netbsd32___getitimer50",
	/* 427 */	"netbsd32___clock_gettime50",
	/* 428 */	"netbsd32___clock_settime50",
	/* 429 */	"netbsd32___clock_getres50",
	/* 430 */	"netbsd32___nanosleep50",
	/* 431 */	"netbsd32_____sigtimedwait50",
	/* 432 */	"#432 (unimplemented netbsd32___mq_timedsend50)",
	/* 433 */	"#433 (unimplemented netbsd32___mq_timedreceive50)",
	/* 434 */	"compat_60_netbsd32__lwp_park",
	/* 435 */	"netbsd32___kevent50",
	/* 436 */	"netbsd32___pselect50",
	/* 437 */	"netbsd32___pollts50",
	/* 438 */	"#438 (unimplemented netbsd32___aio_suspend50)",
	/* 439 */	"netbsd32___stat50",
	/* 440 */	"netbsd32___fstat50",
	/* 441 */	"netbsd32___lstat50",
#if defined(SYSVSEM) || !defined(_KERNEL_OPT)
	/* 442 */	"netbsd32_____semctl50",
#else
	/* 442 */	"#442 (excluded ____semctl50)",
#endif
#if defined(SYSVSHM) || !defined(_KERNEL_OPT)
	/* 443 */	"netbsd32___shmctl50",
#else
	/* 443 */	"#443 (excluded ____shmctl50)",
#endif
#if defined(SYSVMSG) || !defined(_KERNEL_OPT)
	/* 444 */	"netbsd32___msgctl50",
#else
	/* 444 */	"#444 (excluded ____msgctl50)",
#endif
	/* 445 */	"netbsd32___getrusage50",
	/* 446 */	"netbsd32___timer_settime50",
	/* 447 */	"netbsd32___timer_gettime50",
#if defined(NTP) || !defined(_KERNEL_OPT)
	/* 448 */	"netbsd32___ntp_gettime50",
#else
	/* 448 */	"#448 (excluded ___ntp_gettime50)",
#endif
	/* 449 */	"netbsd32___wait450",
	/* 450 */	"netbsd32___mknod50",
	/* 451 */	"netbsd32___fhstat50",
	/* 452 */	"#452 (obsolete 5.99 quotactl)",
	/* 453 */	"netbsd32_pipe2",
	/* 454 */	"netbsd32_dup3",
	/* 455 */	"netbsd32_kqueue1",
	/* 456 */	"netbsd32_paccept",
	/* 457 */	"netbsd32_linkat",
	/* 458 */	"netbsd32_renameat",
	/* 459 */	"netbsd32_mkfifoat",
	/* 460 */	"netbsd32_mknodat",
	/* 461 */	"netbsd32_mkdirat",
	/* 462 */	"netbsd32_faccessat",
	/* 463 */	"netbsd32_fchmodat",
	/* 464 */	"netbsd32_fchownat",
	/* 465 */	"netbsd32_fexecve",
	/* 466 */	"netbsd32_fstatat",
	/* 467 */	"netbsd32_utimensat",
	/* 468 */	"netbsd32_openat",
	/* 469 */	"netbsd32_readlinkat",
	/* 470 */	"netbsd32_symlinkat",
	/* 471 */	"netbsd32_unlinkat",
	/* 472 */	"netbsd32_futimens",
	/* 473 */	"netbsd32___quotactl",
	/* 474 */	"netbsd32_posix_spawn",
	/* 475 */	"#475 (unimplemented { int | netbsd32 | | recvmmsg ( int s , struct mmsghdr * mmsg , unsigned int vlen , unsigned int flags , netbsd32_timespecp_t timeout ) ; })",
	/* 476 */	"#476 (unimplemented { int | netbsd32 | | sendmmsg ( int s , struct mmsghdr * mmsg , unsigned int vlen , unsigned int flags ) ; })",
	/* 477 */	"netbsd32_clock_nanosleep",
	/* 478 */	"netbsd32____lwp_park60",
	/* 479 */	"# filler",
	/* 480 */	"# filler",
	/* 481 */	"# filler",
	/* 482 */	"# filler",
	/* 483 */	"# filler",
	/* 484 */	"# filler",
	/* 485 */	"# filler",
	/* 486 */	"# filler",
	/* 487 */	"# filler",
	/* 488 */	"# filler",
	/* 489 */	"# filler",
	/* 490 */	"# filler",
	/* 491 */	"# filler",
	/* 492 */	"# filler",
	/* 493 */	"# filler",
	/* 494 */	"# filler",
	/* 495 */	"# filler",
	/* 496 */	"# filler",
	/* 497 */	"# filler",
	/* 498 */	"# filler",
	/* 499 */	"# filler",
	/* 500 */	"# filler",
	/* 501 */	"# filler",
	/* 502 */	"# filler",
	/* 503 */	"# filler",
	/* 504 */	"# filler",
	/* 505 */	"# filler",
	/* 506 */	"# filler",
	/* 507 */	"# filler",
	/* 508 */	"# filler",
	/* 509 */	"# filler",
	/* 510 */	"# filler",
	/* 511 */	"# filler",
};