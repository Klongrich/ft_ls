#include "../inc/ls.h"

t_flags		setzero()
{
	t_flags flags;
	
	flags.a = 0;
	flags.l = 0;
	flags.r = 0;
	flags.recr = 0;
	flags.t = 0;
	flags.zero = 0;

	return (flags);
}

int		illegalopt(char c)
{
	ft_putstr_fd("ls: illegal options -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("\nusage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]", 2);
	return (-1);
}

int		parseflags(char **str, t_flags *flags)
{
	while (*str)
	{
		if ((*str)[0] != '-' || !(*str)[1])
			return (0);
		if (**str == '-' && !(*str))
			return (0);
		if (!ft_strcmp(*str, "--"))
		{	
			while (**str)
				(*str)++;
			return (0);
			break;
		}
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
			else if (**str == '1')
				flags->one = 1;
			else
				return (illegalopt(**str));
			(*str)++;
		}
		str++;	
	}
	return (1);
}