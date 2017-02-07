
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int		**sortnums(int **num, int index, int depend);
int		**initsortnums(int **num, int index);

int		checkmonths(char *str)
{
	if (!strcmp(str, "Jan"))
		return (1);
	else if (!strcmp(str, "Feb"))
		return (2);
	else if (!strcmp(str, "Mar"))
		return (3);
	else if (!strcmp(str, "Apr"))
		return (4);
	else if (!strcmp(str, "May"))
		return (5);
	else if (!strcmp(str, "Jun"))
		return (6);
	else if (!strcmp(str, "Jul"))
		return (7);
	else if (!strcmp(str, "Aug"))
		return (8);
	else if (!strcmp(str, "Sep"))
		return (9);
	else if (!strcmp(str, "Oct"))
		return (10);
	else if (!strcmp(str, "Nov"))
		return (11);
	else if (!strcmp(str, "Dec"))
		return (12);
	return (0);
}


void	timesort(char **str)
{
	int i;
	int **nums;
	char *month;
	char *date;
	char *times;
	char *year;
	
	i = 0;
	nums = (int **)malloc(sizeof(int *) * 9);

	while (i < 8)
	{
		month = (char *)malloc(sizeof(char) * 3);
		date = (char *)malloc(sizeof(char) * 2);
		times = (char *)malloc(sizeof(char) * 6);
		year = (char *)malloc(sizeof(char) * 5);

		nums[i] = (int *)malloc(sizeof(int) * 5);
		
		//Month
		month[0] = str[i][4];
		month[1] = str[i][5];
		month[2] = str[i][6];
		month[3] = '\0';

		//Date
		date[0] = str[i][8];
		date[1] = str[i][9];

		//Time
		times[0] = str[i][11];
		times[1] = str[i][12];
		times[2] = str[i][14];
		times[3] = str[i][15];

		//Year
		year[0] = str[i][20];
		year[1] = str[i][21];
		year[2] = str[i][22];
		year[3] = str[i][23];


		nums[i][3] = atoi(year);
		nums[i][0] = checkmonths(month);
		nums[i][1] = atoi(date);
		nums[i][2] = atoi(times);
		nums[i][4] = i;

		free (month);
		free (date);
		free (times);
		free (year);
		i++;
	}

	printf("\n");

	i = 0;
	while (i < 8)
	{
		printf("%d  %d  %d  %d  %d\n", nums[i][0], nums[i][1], nums[i][2], nums[i][3], nums[i][4]);
		i++;
	}
	printf("\n");

	nums = initsortnums(nums, 3);
	nums = sortnums(nums, 0, 1);
	nums = sortnums(nums, 1, 0);
	nums = sortnums(nums, 2, 1);

	i = 0;
	while (i < 8)
	{
		printf("%d  %d  %d  %d  %d\n", nums[i][0], nums[i][1], nums[i][2], nums[i][3], nums[i][4]);
		i++;
	}
}