#include "../inc/ls.h"

t_flags		setzero(void)
{
	t_flags flags;

	flags.a = 0;
	flags.l = 0;
	flags.r = 0;
	flags.recr = 0;
	flags.t = 0;
	flags.zero = 0;
	flags.one = 0;
	flags.numberofargs = 0;
	return (flags);
}

int			illegalopt(char c)
{
	ft_putstr_fd("ls: illegal options -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("\nusage: ls [-lraRt] [file ...]", 2);
	return (-1);
}

t_flags		*setflags(t_flags *flags, char c)
{
	if (c == 'a')
		flags->a = 1;
	else if (c == 'l')
		flags->l = 1;
	else if (c == 'r')
		flags->r = 1;
	else if (c == 'R')
		flags->recr = 1;
	else if (c == 't')
		flags->t = 1;
	else if (c == '1')
		flags->one = 1;
	else
	{
		flags->invaild = 1;
		flags->letter = c;
	}
	return (flags);
}

int			parseflags(char **str, t_flags *flags)
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
		}
		(*str)++;
		while (**str)
		{
			flags = setflags(flags, **str);
			if (flags->invaild == 1)
				return (illegalopt(flags->letter));
			(*str)++;
		}
		str++;
	}
	return (1);
}
