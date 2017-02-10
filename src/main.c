#include "../inc/ls.h"


void	run(char **dirs, char **files, char **argv, t_flags flags)
{
		char **dup;
		char **info;
		char **appendinfo;
		int		len;
		int 	lentwo;

		len = 0;
		dirs = getdirs(argv, &files);
		len = getlength(dirs);
		lentwo = len;
		files = sort(files, flags);
		dirs = sort(dirs, flags);
		if (files)
			printstuff(files, flags, files);
		while (*dirs)
		{
			if (len != 1)
				ft_printf("%~:\n", *dirs);
			info = parsefiles(*dirs, flags);
			info = sort(info, flags);
			appendinfo = apenddir(*dirs, info);
			printstuff(info, flags, appendinfo); 
			if (flags.recr && appendinfo)
			{
				files = (char **)malloc(sizeof(char *) * 50);
				info = (char **)malloc(sizeof(char *) * 50);
				run(files, info, appendinfo, flags);
			}
			if (lentwo != 1)
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
	if (flags.recr)
	{
		appendinfo = apenddir(".//", files);
		files = (char **)malloc(sizeof(char *) * 50);
		info = (char **)malloc(sizeof(char *) * 50);
		run(files, info, appendinfo, flags);
	}
	printstuff(files, flags, files);
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
