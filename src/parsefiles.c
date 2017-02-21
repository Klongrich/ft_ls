#include "../inc/ls.h"

int is_DIR(const char *path)
{
	struct stat path_stat;
	
	stat(path, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

int is_FILE(const char *path)
{
	struct stat path_stat;
	
	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

char	**parsefiles(char *path, t_flags flags)
{
	DIR				*dir;
	struct dirent	*dp;
	char		**str;
	int				i;

	i = 0;
	str = (char **)malloc(sizeof(char *) * 500);
	if (!(dir = opendir(path)))
		ft_printf("Error");
	while ((dp = readdir(dir)))
	{
		if ((flags.a) || (!flags.a && dp->d_name[0] != '.'))
		{
			str[i] = (char *)malloc(sizeof(char) * ft_strlen(dp->d_name) + 1);
			str[i][ft_strlen(dp->d_name)] = '\0'; 
			ft_memcpy(str[i++] , dp->d_name, ft_strlen(dp->d_name));
		}
	}
	return ((char **)str);
}

int		checkend(char *str)
{
	int len; 

	len = ft_strlen(str);
	if (str[len - 1] == '.')
		return (0);
	return (1);
}

char	**apenddir(char *dir, char **files)
{
	int i;
	int j;
	char **stuff;

	i = 0;
	j = 0;
	stuff = (char **)malloc(sizeof(char *) * 70);
	while (files[j])
	{
		if (checkend(files[j]))
		{
			stuff[i] = ft_strjoin("/", files[j]);
			stuff[i] = ft_strjoin(dir, stuff[i]);
			i++;
		}
		j++;
	}
	stuff[i] = 0;
	return (stuff);
}

char	**getdirs(char **argv, char ***files)
{
	char *str;
	char **info;
	char **dup;
	int  i;

	i = 0;
	info = (char **)malloc(sizeof(char *) * 50);
	dup = info;
	while (*argv)
	{
		if ((*argv)[0])
		{
			str = (char *)malloc(sizeof(char *) * 50);
			str = ft_strjoin(".//", *argv);
			if ((*argv)[0] == '/')
				str = *argv;
			if (is_DIR(str))
				*info++ = str;
			else if (is_FILE(str))
				(*files)[i++] = str;
			else
			{
				write(2,"ls: ", 4); 
				write(2, *argv, ft_strlen(*argv));
				write(2, ": No such file or directory\n", 28);
			}
		}
		argv++;
	}
	*info = 0;
	(*files)[i] = 0;
	return (dup);
}
