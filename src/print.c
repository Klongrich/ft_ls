#include "../inc/ls.h"

void	printstuff(char **str, int l)
{
	int i;
	int size;

	size = getlength(str) - 1;
	i = 0;
	l = 0;
	while (i < size)
	{
		ft_printf("%s\n", str[i]);
		i++;
	}
	ft_printf("%s\n", str[i]);
} 