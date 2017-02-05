#include "../inc/ls.h"

void	run(char **dirs, char **files, char **argv, t_flags flags)
{
		char **dup;
		char **info;
		int		len;
		int 	lentwo;
		
		len = 0;
		dirs = getinfo(argv, &files);
		len = getlength(dirs);
		lentwo = len;
		files = sort(files, flags.r, flags.t);
		dirs = sort(dirs, flags.r, flags.t);
		printstuff(files, flags.l);
		while (*dirs)
		{
			dup = dirs;
			if (len != 1)
				ft_printf("%~:\n", *dirs);
			info = parsefiles(*dirs, flags.a);
			info = sort(info, flags.r, flags.t);
			printstuff(info, flags.l);
			if (lentwo != 1)
				ft_printf("\n");
			lentwo--;
			dirs++;
		}
}

int		runblank(char **argv, char **files)
{
	t_flags flags;

	flags = setzero();
	if (parseflags(argv, &flags) == -1)
		return (0);
	files = parsefiles(".", flags.a);
	files = sort(files, flags.r, flags.t);
	printstuff(files, flags.l);
	free(files);
	return (0);
}

int	 main(int argc, char **argv)
{
	t_flags flags;

	char	**files;
	char	**dir;

	files = (char **)malloc(sizeof(char *) * argc + 1);
	dir = (char **)malloc(sizeof(char *) * argc + 1);
	flags = setzero();
	if (argc == 0)
		return (0);
	else
	{			 
		argv++;
		if ((!*argv || (argv[argc - 2][0] == '-')) && argv[argc - 2][1])
			runblank(argv, files);
		else
		{
			if(parseflags(argv, &flags) == -1)
				return (0);
			run(dir, files, argv, flags);
		}
	}
	return (0);
}
