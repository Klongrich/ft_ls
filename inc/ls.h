#ifndef LS_H
# define LS_H
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <dirent.h>
# include <libgen.h>
# include <pwd.h>
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>
# include <grp.h>
# include <time.h>
# include <locale.h>
# include <langinfo.h>
# include <stdio.h>
# include <stdint.h>
# include "../libft/libft.h"

typedef struct		flags
{
	int				a;
	int				l;
	int				r;
	int				recr;
	int				t;
	int				one;
	int				dash;
}					t_flags;

typedef struct		lengts
{
	int 			links;
	int				name;
	int				group;
	int				size;
}

void	ft_printf(char *str, ...);
char	**parsefiles(char *path, int a);
char	**sort(char **str, int r, int t);
int		parseflags(char **str, t_flags *flags);
int		getlength(char **str);
void	printstuff(char **str, int l);
char	**getinfo(char **argv, char ***file);
t_flags	setzero();

#endif
