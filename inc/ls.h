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
	int				zero;
}					t_flags;

typedef struct		lengts
{
	int 			links;
	int				name;
	int				group;
	int				size;
}					t_lengths;

void	ft_printf(char *str, ...);
char	**parsefiles(char *path, t_flags flags);
char	**sort(char **str, t_flags flags);
int		parseflags(char **str, t_flags *flags);
int		getlength(char **str);
void	printstuff(char **str, t_flags flags);
char	**getinfo(char **argv, char ***file);
t_flags	setzero();

#endif
