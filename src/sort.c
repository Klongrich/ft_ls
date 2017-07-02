#include "../inc/ls.h"

int		getlength(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**timesort(char **str, int size, int r)
{
	int			j;
	int			i;
	char		*temp;
	int			flag;
	struct stat	s;
	struct stat	z;

	i = 0;
	j = 0;
	while (i < size)
	{
		flag = 0;
		j = 0;
		while (j < size - i)
		{
			stat(str[j], &s);
			stat(str[j + 1], &z);
			if ((!r && s.st_mtimespec.tv_sec < z.st_mtimespec.tv_sec) ||
				(r && s.st_mtimespec.tv_sec > z.st_mtimespec.tv_sec))
			{
				temp = str[j];
				str[j] = str[j + 1];
				str[j + 1] = temp;
				flag = 1;
			}
			j++;
		}
		if (!flag)
			break ;
		i++;
	}
	return (str);
}

char	**bubblesort(int size, int i, int j, char **str, t_flags flags)
{
	char temp[500];

	while (i++ < size)
	{
		j = i;
		while (j++ < size)
		{
			if ((flags.r && ft_strcmp(str[i], str[j]) < 0) ||
				(!flags.r && ft_strcmp(str[i], str[j]) > 0))
			{
				ft_strcpy(temp, str[i]);
				ft_strcpy(str[i], str[j]);
				ft_strcpy(str[j], temp);
			}
		}
	}
	return (str);
}

char	**sort(char **str, t_flags flags)
{
	int i;
	int j;
	int size;

	size = getlength(str) - 1;
	i = -1;
	j = i;
	if (flags.t)
		return (timesort(str, (getlength(str) - 1), flags.r));
	else
		return (bubblesort(size, i, j, str, flags));
}
