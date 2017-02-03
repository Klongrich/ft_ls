#include "../inc/ls.h"

int is_DIR(const char *path)
{
    struct stat path_stat;
	
	stat(path, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

char	**parsefiles(int a, char *path)
{
	DIR				*dir;
	struct dirent	*dp;
	void			**str;
	void			**dup;

	str = (void **)malloc(sizeof(void *) * 50);
	dup = str;
	if (!(dir = opendir(path)))
		ft_printf("Error");
	while ((dp = readdir(dir)))
	{
		if ((a) || (!a && dp->d_name[0] != '.'))
			*str++ = dp->d_name;
	}
	return ((char **)dup);
}

char	**getdir(char **argv)
{
	char *str;
	char **info;
	char **dup;

	info = (char **)malloc(sizeof(char *) * 50);
	dup = info;
	while (*argv)
	{
		if ((*argv)[0])
		{
			str = ft_strjoin(".//", *argv);
			if (!is_DIR(str))
				ft_printf("./ft_ls: %s: No such file or directory", *argv);
			else
				*info++ = str;
		}
		argv++;
	}
	*info = 0;
	return (dup);
}
