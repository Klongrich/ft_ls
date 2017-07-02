#include "../inc/ls.h"

struct stat statbuf;

t_lengths	set_coloum_sizes(t_lengths m)
{
	struct passwd	*pwd;
	struct group	*grp;

	if ((pwd = getpwuid(statbuf.st_uid)))
		(ft_strlen(pwd->pw_name) > m.name)
		? m.name = ft_strlen(pwd->pw_name) : 0;
	else
		(ft_numlen(statbuf.st_uid) > m.name)
		? m.name = ft_numlen(statbuf.st_uid) : 0;
	if ((grp = getgrgid(statbuf.st_gid)) != NULL)
		(ft_strlen(grp->gr_name) > m.group)
		? m.group = ft_strlen(grp->gr_name) : 0;
	else
		(ft_numlen(statbuf.st_gid) > m.group)
		? m.group = ft_numlen(statbuf.st_gid) : 0;
	(ft_strlen(grp->gr_name) > m.group)
	? m.group = ft_strlen(grp->gr_name) : 0;
	return (m);
}

t_lengths	sizes(char **str)
{
	int			i;
	int			count;
	t_lengths	m;

	m = normzero();
	i = 0;
	count = 0;
	while (str[i])
	{
		lstat(str[i], &statbuf);
		if (ft_numlen(statbuf.st_nlink) > m.links)
			m.links = ft_numlen(statbuf.st_nlink);
		m = set_coloum_sizes(m);
		(ft_numlen(statbuf.st_size) > m.size)
		? m.size = ft_numlen(statbuf.st_size) : 0;
		i++;
		m.count += statbuf.st_blocks;
	}
	return (m);
}	

void		print_name_and_grid(t_lengths m)
{
	struct passwd	*pwd;
	struct group	*grp;

	ft_printf("%*d ", m.links, statbuf.st_nlink);
	if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
		ft_printf("%*s", m.name + 2, pwd->pw_name);
	else
		ft_printf("%*d", m.name + 2, statbuf.st_uid);
	if ((grp = getgrgid(statbuf.st_gid)) != NULL)
		ft_printf("%*s", m.group + 2, grp->gr_name);
	else
		ft_printf("%*d", m.group + 2, statbuf.st_gid);
}

char	*cutstring(char *str)
{
	int i;
	int j;
	char *new;

	j = -1;
	i = ft_strlen(str);
	new = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	while(str[i] != '/')
		i--;
	i--;
	while (j++ < i)
		new[j] = str[j];
	new[j] = '\0';
	return (new);
}

int check_root_link(char *str)
{
	struct stat stuff;

	lstat(cutstring(str), &stuff);
	if (S_ISLNK(stuff.st_mode))
		return(1);
	else
		return(0);
}

int	check_files_link(char *str)
{
	struct stat stuff;

	lstat(str, &stuff);
	if (S_ISLNK(stuff.st_mode))
		return(1);
	else
		return(0);
}

void	only_link(char *linkfolder)
{
	char	**str;
	t_lengths		m;
	int 			i;
	size_t			len;
	char			buff[1024];

	len = readlink(linkfolder, buff, 1023);
	buff[len] = '\0';
	i = 0;
	str = (char **)malloc(sizeof(char *) * 2);
	str[0] = (char *)malloc(sizeof(char) * ft_strlen(linkfolder) + 1);
	str[0] = linkfolder;
	m = sizes(str);
	lstat(str[i], &statbuf);
	print_permissons(statbuf);
	print_name_and_grid(m);
	ft_printf("%*d", m.size, (int)statbuf.st_size);
	print_time(str[i]);
	ft_printf("%s -> %s\n", str[i], buff);
}

void	print_file_name(char *filepath, char *name)
{
	size_t			len;
	char			buff[1024];

	filepath++;
	if (check_files_link(filepath))
	{
		len = readlink(filepath, buff, 1023);
		buff[len] = '\0';
		ft_printf("%s -> %s\n", name, buff);
	}
	else
		ft_printf("%s\n", name);
}

int			long_format_init(char **str, char **name)
{
	t_lengths	m;
	int			i;

	i = 0;
	if (!*str || !*name)
		return (0);
	if (check_root_link(str[i]))
		only_link(cutstring(str[0]));
	else
	{
		m = sizes(str);
		ft_printf("total %d\n", m.count);
		while (str[i])
		{
			lstat(str[i], &statbuf);
			print_permissons(statbuf);
			print_name_and_grid(m);
			if (S_ISCHR(statbuf.st_mode) || S_ISBLK(statbuf.st_mode))
			{
				ft_printf("%*d,", 5, major(statbuf.st_rdev));
				ft_printf("%*d", 5, minor(statbuf.st_rdev));
			}
			else
				ft_printf("%*d", m.size, (int)statbuf.st_size);
			print_time(str[i]);
			print_file_name(str[i], name[i]);
			i++;
		}
	}
	return (1);
}

void		printstuff(char **str, t_flags flags, char **filepath)
{
	int i;

	i = 0;
	if (flags.l)
		long_format_init(filepath, str);
	else
	{
		while (str[i])
		{
			ft_printf("%s\n", str[i]);
			i++;
		}
	}
}
