#include "../inc/ls.h"

/*
check for ../../../ && ..../ && * 
*/

int		error()
{
	ft_printf("not supported sorry :( \n");
	return (0);
}

int	 main(int argc, char **argv)
{
	t_flags flags;
	char	**list;

	flags = setzero();
	if (argc == 0)
		return (0);
	else
	{			 
		argv++;
		if (argc > 1)
			parseflags(argv, &flags);

		list = parsefiles(flags.a, ".");

		list = sort(list, flags.r);

		printstuff(list, 0);
		
		printf("\n\n");
		printflags(flags);
	}
	return (0);
}
