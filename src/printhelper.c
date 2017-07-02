#include "../inc/ls.h"

void		print_permissons(struct stat stuff)
{
	ft_putchar((S_ISFIFO(stuff.st_mode)) ? 'p' : '\0');
	ft_putchar((S_ISCHR(stuff.st_mode)) ? 'c' : '\0');
	ft_putchar((S_ISDIR(stuff.st_mode)) ? 'd' : '\0');
	ft_putchar((S_ISBLK(stuff.st_mode)) ? 'b' : '\0');
	ft_putchar((S_ISREG(stuff.st_mode)) ? '-' : '\0');
	ft_putchar((S_ISLNK(stuff.st_mode)) ? 'l' : '\0');
	ft_putchar((S_ISSOCK(stuff.st_mode)) ? 's' : '\0');
	ft_putchar((stuff.st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((stuff.st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((stuff.st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((stuff.st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((stuff.st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((stuff.st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((stuff.st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((stuff.st_mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((stuff.st_mode & S_IXOTH) ? 'x' : '-');
	ft_putchar(' ');
	ft_putchar(' ');
}

void		print_time(char *str)
{
	//time_t		now;
	char		*times;
	struct stat	statbuf;

	//struct tm	*tm;

	/*
	now = time(0);
	tm = localtime(&now);
	printf("Current time %02d:\n", tm->tm_mon + 1);
	*/

	lstat(str, &statbuf);
	times = (char *)malloc(sizeof(char) * 40);
	times = ctime(&statbuf.st_mtime);
	times += 3;

	/*
	printf("Time: %ld\n", statbuf.st_mtime);
	if (S_ISLNK(statbuf.st_mode))
	{
		times += 17;
		ft_printf("%.*s %s\n", 7, times, name);
	}
	*/
	ft_printf("%.*s ", 13, times);
}

t_lengths	normzero(void)
{
	t_lengths m;

	m.links = 0;
	m.name = 0;
	m.group = 0;
	m.size = 0;
	m.count = 0;
	return (m);
}
