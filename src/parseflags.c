#include "../inc/ls.h"

void	printflags(t_flags stuff)
{
	printf("a: %d\n", stuff.a);
	printf("l: %d\n", stuff.l);
	printf("r: %d\n", stuff.r);
	printf("R: %d\n", stuff.recr);
	printf("t: %d\n", stuff.t);
}

t_flags		setzero()
{
	t_flags flags;
	
	flags.a = 0;
	flags.l = 0;
	flags.r = 0;
	flags.recr = 0;
	flags.t = 0;

	return (flags);
}

int		parseflags(char **str, t_flags *flags)
{
	while (*str)
	{
		if ((*str)[0] != '-' || !(*str)[1])
			return (0);
		(*str)++;
		while (**str)
		{
			if (**str == 'a')
				flags->a = 1;
			else if (**str == 'l')
				flags->l = 1;
			else if (**str == 'r')
				flags->r = 1;
			else if (**str == 'R')
				flags->recr = 1;
			else if (**str == 't')
				flags->t = 1;
			else
				return (0);
			(*str)++;
		}
		str++;	
	}
	return (1);
}