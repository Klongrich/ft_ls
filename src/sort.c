#include "../inc/ls.h"

int		getlength(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**sort(char **str, int r)
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
			if ((r && strcmp(str[i], str[j]) < 0) || 
				(!r && strcmp(str[i], str[j]) > 0))
			{
				strcpy(temp, str[i]);
				strcpy(str[i], str[j]);
				strcpy(str[j], temp);
			}
		}	
	}	
	return (str);
}