
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	int arr[] = {0, 1, 2, 3, 4, 5};
	int	*zone;
	int len = 6;
	int num_of_ants = 3;
	int	num_of_ant_in_tube = 1;
	int	ant_on_start = 0;
	int	count_temp = num_of_ants;
	int count_end = 0;
	int i = -1;
	int j = -1;

	zone = malloc(4 * (len + 1));
	while (++i < len + 1)
		zone[i] = 0;
	while (count_end != num_of_ants - 1)
	{
		(j < len) ? j++ : 0;
		i = j;

		(j == len) ? count_end++ : 0;
		while (i > 0)
		{
			(j ) ? (zone[i] = zone[i - 1]) : 0;
			(i < len && zone[i]) ? printf("L%d-%d ", zone[i], arr[i]) : 0;
			i--;
		}
		if (count_temp == 0)
			zone[0] = 0;
		if (count_temp > 0)
		{
			(j > 0) ? (zone[1] = zone[0]) : 0;
			zone[0] = num_of_ant_in_tube;
			printf("L%d-%d ", zone[0], arr[0]);
			num_of_ant_in_tube++;
			count_temp--;
		}
		putchar('\n');
	}
	return (0);
}