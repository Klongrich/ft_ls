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

char	**parsefiles(char *path, int a)
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
	closedir(dir);
	return ((char **)dup);
}

char	**getinfo(char **argv, char ***files)
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
			str = ft_strjoin(".//", *argv);
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
