#include "../inc/ls.h"

int is_regular_file(const char *path)
{
    struct stat path_stat;
	
	stat(path, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

void	setdir(char **argv)
{
	char *str;
	char **dup;

	dup = argv;
	while (*dup)
	{
		if (dup)
		{
			str = ft_strjoin(".//", *dup);
			printf("%s\n", str);
			printf("Check: %d\n", is_regular_file(str));
		}
		dup++;
	}
	printf("\n");
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