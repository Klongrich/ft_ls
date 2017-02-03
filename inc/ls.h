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
# include "../libft/libft.h"

typedef struct		flags
{
	int				a;
	int				l;
	int				r;
	int				recr;
	int				t;
}					t_flags;

void	ft_printf(char *str, ...);

char	**parsefiles(int a, char *path);
char	**sort(char **str, int r);

int		parseflags(char **str, t_flags *flags);
int		getlength(char **str);

void	printstuff(char **str, int l);
void	printflags(t_flags stuff);

char 	**getdir(char **argv);

t_flags	setzero();

#endif
