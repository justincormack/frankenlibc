/* platform specific initialization before we hand over to generic code */

/* move to a header somewhere */
int __franken_start_main(int (*)(int,char **,char **), int, char **, char **);

extern int main(int, char **, char **);

int
_start1(void (*fnp)(void), int argc, char **argv)
{
	char **envp = argv + argc + 1;

	return __franken_start_main(main, argc, argv, envp);
}
