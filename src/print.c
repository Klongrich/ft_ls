#include "../inc/ls.h"

void	printpermissons(struct stat stuff)
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

}

void	printtime(char *str, char *name)
{
		char *time;
		char *start;
		struct stat statbuf;

		stat(str, &statbuf);
		time = (char *)malloc(sizeof(char) * 40);
		start = time;
		time = ctime(&statbuf.st_mtime);
		time += 3;

		printf("%.*s %s\n", 13, time, name);
		free(start);
}

t_lengths		sizes(char **str)
{
	int i;
	int	count;
	struct stat statbuf;
	struct passwd  *pwd;
	struct group   *grp;

	t_lengths	m;

	i = 0;
	m.links = 0;
	m.name = 0;
	m.group = 0;
	m.size = 0;
	count = 0;
	while (str[i])
	{
		stat(str[i], &statbuf);

		if (ft_numlen(statbuf.st_nlink) > m.links)
			m.links = ft_numlen(statbuf.st_nlink);
		
		if ((pwd = getpwuid(statbuf.st_uid)))
		{
			if (ft_strlen(pwd->pw_name) > m.name)
				m.name = ft_strlen(pwd->pw_name);
		}
		else
		{
			if (ft_numlen(statbuf.st_uid) > m.name)
				m.name = ft_numlen(statbuf.st_uid);
		}

		if ((grp = getgrgid(statbuf.st_gid)) != NULL)
		{
			if (ft_strlen(grp->gr_name) > m.group)
				m.group = ft_strlen(grp->gr_name);
		}
		else
		{
			if (ft_numlen(statbuf.st_gid) > m.group)
				m.group = ft_numlen(statbuf.st_gid);
		}
		
		if (ft_strlen(grp->gr_name) > m.group)
			m.group = ft_strlen(grp->gr_name);
		
		if (ft_numlen(statbuf.st_size) > m.size)
			m.size = ft_numlen(statbuf.st_size);
		i++;
		count += statbuf.st_blocks;
	}
	ft_printf("total %d\n", count);
	return (m);
}

void	complexprint(char **str, char **name)
{
	struct stat	 statbuf;
	struct passwd  *pwd;
	struct group   *grp;
	t_lengths		m;
	int i;

	i = 0;
	m = sizes(str);
	while (str[i])
	{
		stat(str[i], &statbuf);
		printpermissons(statbuf);
		ft_printf("%*d" , m.links + 2 , statbuf.st_nlink);

		if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
			ft_printf("%*s", m.name + 1, pwd->pw_name);
		else
			ft_printf("%*d", m.name + 1, statbuf.st_uid);

		if ((grp = getgrgid(statbuf.st_gid)) != NULL)
			ft_printf("%*s", m.group + 2, grp->gr_name);
		else
			ft_printf("%*d", m.group + 2, statbuf.st_gid);

		if (S_ISCHR(statbuf.st_mode) || S_ISBLK(statbuf.st_mode) )
		{
			ft_printf("%*d", 5, major(statbuf.st_rdev));
			ft_printf("%*d", 5, minor(statbuf.st_rdev));
		} 
		else 
		{
			ft_printf("%*d", m.size + 2, (int)statbuf.st_size);
		} 
		printtime(str[i], name[i]);
		i++;
	}
}

void	printstuff(char **str, t_flags flags, char **complex)
{
	int i;

	i = 0;
	if (flags.l)
		complexprint(complex, str);
	else
	{
		while (str[i])
		{
			ft_printf("%s\n", str[i]);
			i++;
		}
	}
}