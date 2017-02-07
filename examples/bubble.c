#include <stdio.h>

int		**initsortnums(int **num, int index)
{
	int j;
	int i;
	int	*temp;
	int flag;

	i = 0;
	j = 0;
	while (i < 7)
	{
		flag = 0;
		j = 0;
		while (j < 7 - i)
		{
			if (num[j][index] < num[j + 1][index])
			{
				temp = num[j];
				num[j] = num[j + 1];
				num[j + 1] = temp;
				flag = 1;
			}
			j++;
		}
		if (!flag)
			break ;
		i++;
	}
	return (num);
}

int		**sortnums(int **num, int index, int depend)
{
	int j;
	int i;
	int	*temp;
	int flag;

	i = 0;
	j = 0;
	while (i < 7)
	{
		flag = 0;
		j = 0;
		while (j < 7 - i)
		{
			if(num[j][depend] == num[j + 1][depend])
			{
				if (num[j][index] < num[j + 1][index])
				{
					temp = num[j];
					num[j] = num[j + 1];
					num[j + 1] = temp;
					flag = 1;
				}
			}
			j++;
		}
		if (!flag)
			break ;
		i++;
	}
	return (num);
}
