/* platform specific initialization before we hand over to generic code */

/* move to a header somewhere */
int __libc_start_main(int (*)(int,char **,char **), int, char **, char **);

#define AUX_CNT 38

int
__platform_init(int (*main)(int,char **,char **), int argc, char **argv)
{
	char **envp = argv + argc + 1;

	/* XXX pull stuff from aux vector */

	return __libc_start_main(main, argc, argv, envp);
}
