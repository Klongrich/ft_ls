#include "../inc/ls.h"

void	printpermissons(struct stat stuff)
{
	ft_putchar((S_ISDIR(stuff.st_mode)) ? 'd' : '-');
	ft_putchar((stuff.st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((stuff.st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((stuff.st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((stuff.st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((stuff.st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((stuff.st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((stuff.st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((stuff.st_mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((stuff.st_mode & S_IXOTH) ? 'x' : '-');

}

void	printtime(char *str)
{
		char *time;
		char *start;
		struct stat statbuf;
	
		stat(str, &statbuf);
		time = (char *)malloc(sizeof(char) * 40);
		start = time;
		time = ctime(&statbuf.st_mtime);
		time += 3;

		printf("%.*s %s\n", 13, time, str);
		//free(start);
}

lengths		sizes(char **str)
{
	int i;
	struct stat statbuf;

	i = 0;
	while (str[i])
	{
		stat(str[i], &statbuf);
		

	}
}

void	complexprint(char **str)
{
	struct stat	 statbuf;
	struct passwd  *pwd;
	struct group   *grp;
	struct lengths	m;
	int i;

	i = 0;
	m = sizes(str);
	while (str[i])
	{
		stat(str[i], &statbuf);
		printpermissons(statbuf);
		printf("%*d" , 3, statbuf.st_nlink);

		if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
			printf("%*s",9, pwd->pw_name);
		else
			printf("%*d", 9, statbuf.st_uid);

		if ((grp = getgrgid(statbuf.st_gid)) != NULL)
			printf("%*s", 9, grp->gr_name);
		else
			printf("%*d", 9, statbuf.st_gid);

		printf("%*d", 6, (int)statbuf.st_size);
		printtime(str[i]);
		i++;
	}
}

void	printstuff(char **str, int l)
{
	int i;
	int last;

	last = getlength(str);
	i = 0;
	if (l)
		complexprint(str);
	else
	{
		while (str[i])
		{
			ft_printf("%s\n", str[i]);
			i++;
		}
		if (i != last)
			ft_printf("\n");
	}
}