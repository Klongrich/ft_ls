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
	char 	**dirs;

	flags = setzero();
	if (argc == 0)
		return (0);
	else
	{			 
		argv++;
		if (argc > 1)
			parseflags(argv, &flags);

		dirs = getdir(argv);
		dirs = sort(dirs, flags.r);
		
		int i;

		i = 0;
		while (dirs[i])
		{
			printf("DIR: %s\n", dirs[i]);
			i++;
		}
		/*
		info = parsefiles(flags.a, str);
		info = sort(info , flags.r);
		*/
		printflags(flags);
	}
	return (0);
}
