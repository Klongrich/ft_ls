#include "../inc/ls.h"

void	ft_printf(char *str, ...)
{
	va_list list;

	va_start(list, str);
	while (*str)
	{
		while (*str != '%' && *str)
		{
			ft_putchar(*str);
			str++;
		}
		if (!*str)
			break ;
		str++;
		if (*str == 'd')
			ft_putnbr(va_arg(list, int));
		else if (*str == 's')
			ft_putstr(va_arg(list, char*));
		str++;
	}
}
