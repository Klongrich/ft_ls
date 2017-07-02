#include "../inc/ls.h"

void	printdir(char *str)
{
	int i;

	i = 0;
	while (str[i] == '/' || str[i] == '.')
	{
		i++;
	}
	ft_printf("./");
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	ft_putchar(':');
	ft_putchar('\n');
}

char	**setinfo(char **dirs, t_flags flags)
{
	char **info;

	info = NULL;
	if (*dirs)
	{
		info = parsefiles(*dirs, flags);
		info = sort(info, flags);
	}
	return (info);
}
