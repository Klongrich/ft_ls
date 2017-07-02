#include "../inc/ls.h"

void	prints(char **str)
{
	int i;

	i = 0;
	while(str[i])
	{
		ft_printf("%s\n", str[i]);
		i++;
	}
}

void	printdirtwo(char *str)
{
	int i;

	i = 3;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	ft_putchar(':');
	ft_putchar('\n');
}

void	recur(char **dirs, char **files, char **argv, t_flags flags, char *top)
{
	char **info;
	char **appendinfo;

	dirs = getdirs(argv, &files);
	files = sort(files, flags);
	dirs = sort(dirs, flags);
	info = setinfo(dirs, flags);
	while (*dirs)
	{
		if (!flags.numberofargs)
			printdir(*dirs);
		else if (flags.numberofargs == 2)
			printdirtwo(*dirs);
		info = parsefiles(*dirs, flags);
		info = sort(info, flags);
		appendinfo = apenddir(*dirs, info, flags);
		printstuff(info, flags, appendinfo);
		if (appendinfo)
		{
			if (ft_strcmp(*dirs, top))
				ft_printf("\n");
			files = (char **)malloc(sizeof(char *) * 500);
			info = (char **)malloc(sizeof(char *) * 500);
			recur(files, info, appendinfo, flags, top);
		}
		dirs++;
	}
}

int		check_order(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] - s2[i] > 0)
			return (0);
		else if (s1[i] - s2[i] < 0)
			return (1);
		i++;
	}
	return (0);
}

char  *check_last(char *path, t_flags flags)
{
	int i;
	int loop;
	struct stat info;
	char **filename;
	char *temp;
	char *answer;

	i = 0;
	filename = parsefiles(path, flags);
	path = ft_strjoin(path, "/");
	answer = NULL;
	while (filename[i])
	{
		temp = ft_strjoin(path, filename[i]);
		lstat(temp, &info);
		if (S_ISDIR(info.st_mode))
		{
			if (!answer)
				answer = temp;
			if (check_order(answer, filename[i]))
				answer = temp;
			loop = 1;
		}
		temp = path;
		i++;
	}
	return (answer);
}

char	*settop(char **str, t_flags flags)
{
	char **files;
	char **dirs;
	char *lastword;

	files = (char **)malloc(sizeof(char *) * 400);
	dirs = (char **)malloc(sizeof(char *) * 400);
	dirs = getdirs(str, &files);
	dirs = sort(dirs, flags);
	lastword = dirs[getlength(dirs) - 1];
	parsefiles(lastword, flags);
	return (check_last(lastword, flags));
}

int		numberofargs(char **str)
{
	int answer;

	answer = 2;
	if (getlength(str) == 2)
		answer = 1;
	return (answer);
}

int		arg_is_file(char *str)
{
	if (is_file(str))
	{
		ft_printf("%s\n", str);
		return (1);
	}
	return (0);
}

void	run(char **dirs, char **info, int len, int lentwo, t_flags flags)
{
	char **appendinfo;

	while (*dirs)
	{
		if (!arg_is_file(*dirs))
		{
			if (len != 1)
				ft_printf("%~:\n", *dirs);
			info = parsefiles(*dirs, flags);
			info = sort(info, flags);
			appendinfo = apenddir(*dirs, info, flags);
			printstuff(info, flags, appendinfo);
			if (lentwo != 1)
				ft_printf("\n");
			lentwo--;
			dirs++;
		}
	}
}

void	init(char **dirs, char **files, char **argv, t_flags flags)
{
	int		len;
	int		lentwo;
	char	**info;

	info = NULL;
	len = 0;
	if (flags.recr)
	{
		flags.numberofargs = numberofargs(argv);
		recur(dirs, files, argv, flags, settop(argv, flags));
	}
	else
	{
		dirs = getdirs(argv, &files);
		len = getlength(dirs);
		lentwo = len;
		files = sort(files, flags);
		dirs = sort(dirs, flags);
		if (*dirs)
		{
			info = parsefiles(*dirs, flags);
			info = sort(info, flags);
		}
		run(dirs, info, len, lentwo, flags);
	}
}

int		runblank(char **argv, char **files, char **dirs)
{
	t_flags		flags;
	char		**appendinfo;
	char		**info;

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
		appendinfo = apenddir(".//", files, flags);
		files = (char **)malloc(sizeof(char *) * 500);
		info = (char **)malloc(sizeof(char *) * 500);
		recur(files, info, appendinfo, flags, settop(appendinfo, flags));
	}
	free(files);
	return (0);
}

int		main(int argc, char **argv)
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
			if (parseflags(argv, &flags) == -1)
				return (0);
			init(dir, files, argv, flags);
		}
	}
	return (0);
}
