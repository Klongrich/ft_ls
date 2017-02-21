#include "../inc/ls.h"


void	printdir(char *str)
{
	int i;

	i = 0;
	while (str[i] == '/' || str[i] == '.')
	{
		i++;
	}
	ft_printf("./");
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	ft_putchar(':');
	ft_putchar('\n');
}

void	run(char **dirs, char **files, char **argv, t_flags flags)
{
		char **info;
		char **appendinfo;
		char **temp;
		char **aptemp;
		int		len;
		int 	lentwo;

		len = 0;
		dirs = getdirs(argv, &files);
		len = getlength(dirs);
		lentwo = len;
		files = sort(files, flags);
		dirs = sort(dirs, flags);
		info = parsefiles(*dirs, flags);
		info = sort(info, flags);

		while (*dirs)
		{
			if (flags.recr)
				printdir(*dirs);
			else
			{
				if (len != 1)
					ft_printf("%~:\n", *dirs);
			}
			temp = info;
			info = parsefiles(*dirs, flags);
			info = sort(info, flags);
			appendinfo = apenddir(*dirs, info);
			aptemp = appendinfo;
			printstuff(info, flags, appendinfo);
			if (flags.recr && appendinfo)
			{
				ft_printf("\n");
				files = (char **)malloc(sizeof(char *) * 50);
				info = (char **)malloc(sizeof(char *) * 50); 
				run(files, info, appendinfo, flags);
			}
			if (lentwo != 1 && !flags.recr)
				ft_printf("\n");
			lentwo--;
			dirs++;
		}
}

int		runblank(char **argv, char **files, char **dirs)
{
	t_flags flags;
	char **appendinfo;
	char **info;

	flags = setzero();
	if (parseflags(argv, &flags) == -1)
		return (0);
	dirs = getdirs(argv, &files);
	files = parsefiles(".", flags);
	files = sort(files, flags);
	printstuff(files, flags, files);
	if (flags.recr)
	{
		printf("\n");
		appendinfo = apenddir(".//", files);
		files = (char **)malloc(sizeof(char *) * 50);
		info = (char **)malloc(sizeof(char *) * 50);
		run(files, info, appendinfo, flags);
	}
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
		if ((!*argv || (argv[argc - 2][0] == '-')) && argv[argc - 2][1] 
			&& ft_strcmp(argv[argc - 2], "--"))
			runblank(argv, files, dir);
		else
		{
			if(parseflags(argv, &flags) == -1)
				return (0);
			run(dir, files, argv, flags);
		}
	}
	return (0);
}
