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
	int j;
	int i;
	char	*temp;
	int flag;
	struct stat s;
	struct stat z;

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
			if ( (!r && s.st_mtime < z.st_mtime) ||
				(r && s.st_mtime > z.st_mtime))
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


char	**sort(char **str, t_flags flags)
{
	int i;
	int j;
	int size;
	char temp[500];

	size = getlength(str) - 1;
	i = -1;
	while (i++ < size)
	{
		j = i;
		while(j++ < size)
		{
			if ((flags.r && strcmp(str[i], str[j]) < 0) || 
				(!flags.r && strcmp(str[i], str[j]) > 0))
			{
				strcpy(temp, str[i]);
				strcpy(str[i], str[j]);
				strcpy(str[j], temp);
			}
		}	
	}
	if (flags.t)
		return (timesort(str, (getlength(str) - 1), flags.r));
	else
		return (str);	
	}	