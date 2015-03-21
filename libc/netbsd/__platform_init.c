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

/* The second argument is an Obj_Entry from libexec/ld.elf_so/rtld.h
   this contains TLS information; we will need to include the headers */

int
__platform_init(void (*cleanup)(void), const void *obj, struct ps_strings *ps_strings)
{

	return __franken_start_main(main, ps_strings->ps_nargvstr, ps_strings->ps_argvstr, ps_strings->ps_envstr);
}
