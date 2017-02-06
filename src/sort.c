#include "../inc/ls.h"

int		getlength(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**timesort(char **str)
{
	char *time;
	char *start;
	struct stat statbuf;

	stat(".//", &statbuf);
	time = (char *)malloc(sizeof(char) * 40);
	start = time;
	time = ctime(&statbuf.st_mtime);
	time += 3;
	
	ft_printf("%.13s %s\n", time,  *str);
	free(start);


	return (0);
}

char	**sort(char **str, t_flags flags)
{
	int i;
	int j;
	int size;
	char temp[500];

	if (flags.t)
		return (timesort(str));
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
	return (str);
}