#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>

#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdio.h>
#include <stdint.h>

#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>

void	timesort(char **str);

void	ft_putchar(char c)
{
	write(1, &c, 1);
}


void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*ret;

	ret = dst;
	while (n--)
		*(unsigned char *)dst++ = *(unsigned char*)src++;
	return (ret);
}

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

void		getsize()
{
	DIR *dir;
	struct dirent	*dp;
	struct stat		s;
	int 			count;

	count = 0;
	dir = opendir(".");
	while ((dp = readdir(dir)) != NULL)
	{
		if (dp->d_name[0] != '.')
		{
			stat(dp->d_name, &s);
			count += (int)s.st_size;
			printf("%d\n", (int)s.st_size);
		}
	}
	closedir(dir);
	printf("total %d\n", count / 512);
}

int main()
{
	DIR 			*dir;
	char			**str;
	struct dirent	*dp;
	struct stat	 statbuf;
	int				i;
	//struct passwd  *pwd;
	//struct group   *grp;
	
	i = 0;
	str = (char **)malloc(sizeof(char *) * 20);
	dir = opendir(".//");
	// getsize();
	/* Loop through directory entries. */
	while ((dp = readdir(dir)) != NULL) 
	{
		if (dp->d_name[0] == '.')
		{

		}
		else
		{
			///* Get entry's information. */
			//if (stat(dp->d_name, &statbuf) == -1)
			//	continue;
			//	 
			///* Print out type, permissions, and number of links. */
			//printpermissons(statbuf);
			//printf("%3d" , statbuf.st_nlink);
			// 
			///* Print out owner's name if it is found using getpwuid(). */
			//if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
			//	printf("%9s", pwd->pw_name);
			//else
			//	printf("%*d", 9 , statbuf.st_uid);
			//	 
			///* Print out group name if it is found using getgrgid(). */
			//if ((grp = getgrgid(statbuf.st_gid)) != NULL)
			//	printf("%9s", grp->gr_name);
			//else
			//	printf("%9d", statbuf.st_gid);
			//	 
			///* Print size of file. */
			//printf("%6d", (int)statbuf.st_size);
			// 
			///* Prints out time */


			char  *time;
			stat(dp->d_name, &statbuf);

			time = (char *)malloc(sizeof(char) * 40);
			str[i] = (char *)malloc(sizeof(char) * 40);
		
			time = ctime(&statbuf.st_mtime);
			
			/*
			int j;

			j = 0;
			while (time[j])
			{
				str[i][j] = time[j];
				j++;
			}
			*/
			ft_memcpy(str[i], time, 24);
			//str[i] = ctime(&statbuf.st_mtime);
			str[i][24] = '\0';
			printf("%.26s %d\n" , str[i], i);
			i++;
		}
	}

	str[i] = 0;
	closedir(dir);

	timesort(str);
}	
