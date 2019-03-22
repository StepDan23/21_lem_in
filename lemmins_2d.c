

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	ft_is_finished_all(int *start, int *end, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (start[i] != end[i])
			return (1);
		i++;
	}
	return (0);
}

int main(void)
{
	int arr[2][6] = {
		{0, 11, 12, 13, 14, 5},
		{0, 26, 27, 28, 29, 5}
	};
	int	ways_count = 2;
	int	len[] = {6, 6};
	int	ant_start[] = {9, 9};
	int	ant_finished[] = {0, 0};
	int	ant_left[] = {9, 5};
	int	num_of_ant_in_tube = 1;
	int	k;
	int	i;
	int	j[] = {0, 0};
	int	**zone;

	i = 0;
	zone = malloc(8 * ways_count);
	while (i < ways_count)
	{
		zone[i] = malloc(4 * len[i] + 4);
		i++;
	}
	k = 0;
	while (ft_is_finished_all(ant_start, ant_finished, ways_count))
	{
		if (ant_start[k] != ant_finished[k])
		{

			i = (j[k] < len[k]) ? j[k]++ : j[k];
			(j[k] == len[k]) ? ant_finished[k]++ : 0;
			while (i > 0)
			{
				(j[k]) ? (zone[k][i] = zone[k][i - 1]) : 0;
				(i < len[k] && zone[k][i]) ? printf("L%d-%d ", zone[k][i], arr[k][i]) : 0;
				i--;
			}
			if (ant_left[k] == 0)
				zone[k][0] = 0;
			if (ant_left[k] > 0)
			{
				zone[k][0] = num_of_ant_in_tube;
				num_of_ant_in_tube++;
				ant_left[k]--;
			}
		}
		k = (k + 1) % ways_count;
		(k == 0) ? putchar('\n') : 0;
	}
	(k != 0) ? putchar('\n') : 0;
	return (0);
}
