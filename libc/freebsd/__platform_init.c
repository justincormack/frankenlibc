/* platform specific initialization before we hand over to generic code */

/* move to a header somewhere */
int __franken_start_main(int (*)(int,char **,char **), int, char **, char **);

struct ps_strings {
	char	**ps_argvstr;	/* first of 0 or more argument strings */
	int	ps_nargvstr;	/* the number of argument strings */
	char	**ps_envstr;	/* first of 0 or more environment strings */
	int	ps_nenvstr;	/* the number of environment strings */
};

extern int main(int, char **, char **);

int
__platform_init(int argc, char **argv, char **envp)
{

	return __franken_start_main(main, argc, argv, envp);
}
