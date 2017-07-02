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
	int				invaild;
	char			letter;
	int				numberofargs;
}					t_flags;

typedef struct		lengts
{
	int 			links;
	int				name;
	int				group;
	int				size;
	int				count;
}					t_lengths;

void		ft_printf(char *str, ...);
char		**parsefiles(char *path, t_flags flags);
char		**sort(char **str, t_flags flags);
int			parseflags(char **str, t_flags *flags);
int			getlength(char **str);
void		printstuff(char **str, t_flags flags, char **complex);
char		**getdirs(char **argv, char ***file);
char		**apenddir(char *dir, char **files, t_flags flags);
int			is_dir(const char *path);
int			is_file(const char *path);
void		printdir(char *str);
char		**setinfo(char **dirs, t_flags flags);
void		print_permissons(struct stat buff);
void		print_time(char *str);
char		**recrdir(char **argv, char ***files);
char		**init_dirs(char **argv, char ***files);

t_lengths	normzero(void);
t_flags		setzero();
#endif

// @ extended attributes
// + extened security info
// more than 6 months = year
// -R on 3 files+ deep
// -t final sort
// -lR /etc to only show links.
// -R /dev

