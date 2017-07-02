#include "../inc/ls.h"

int		ft_argv_len(char **argv)
{
	int i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

char	**parsefiles(char *path, t_flags flags)
{
	DIR				*dir;
	struct dirent	*dp;
	char			**str;
	int				i;

	i = 0;
	str = malloc(sizeof(*str) * 500);
	if (!(dir = opendir(path)))
		ft_printf("Error");
	while ((dp = readdir(dir)))
	{
		if ((flags.a) || (!flags.a && dp->d_name[0] != '.'))
		{
			str[i] = malloc(sizeof(str[i]) * sizeof(dp->d_name) + 1);
			str[i][ft_strlen(dp->d_name)] = '\0';
			ft_memcpy(str[i++], dp->d_name, ft_strlen(dp->d_name));
		}
	}
	return ((char **)str);
}

int		checkend(char *str)
{
	int len;

	len = ft_strlen(str);
	if (!ft_strcmp(str, ".") || !ft_strcmp(str, ".."))
		return (0);
	return (1);
}

char	**apenddir(char *dir, char **files, t_flags flags)
{
	int		i;
	int		j;
	char	**stuff;

	i = 0;
	j = 0;
	stuff = malloc(sizeof(*stuff) * ft_argv_len(files) + 1);
	while (files[j])
	{
		if (checkend(files[j]) || !flags.recr)
		{
			if (!strcmp(".//", dir))
				stuff[i] = ft_strjoin(".//", files[j]);
			else
			{
				stuff[i] = ft_strjoin("/", files[j]);
				stuff[i] = ft_strjoin(dir, stuff[i]);
			}
			i++;
		}
		j++;
	}
	stuff[i] = 0;
	return (stuff);
}

void	printerror(char *str)
{
	write(2, "ls: ", 4);
	write(2, str, ft_strlen(str));
	write(2, ": No such file or directory\n", 28);
}

char	**getdirs(char **argv, char ***files)
{
	char	*str;
	char	**info;
	char	**dup;
	int		i;

	i = 0;
	info =	malloc(sizeof(*info) * ft_argv_len(argv) + 1);
	dup = info;
	while (*argv)
	{
		if ((*argv)[0])
		{
			str = *argv;
			if ((*argv)[0] == '/')
				str = *argv;
			if (is_dir(str))
				*info++ = str;
			else if (is_file(str))
				(*files)[i++] = str;
			else
				printerror(*argv);
		}
		argv++;
	}
	*info = 0;
	(*files)[i] = 0;
	return (dup);
}
