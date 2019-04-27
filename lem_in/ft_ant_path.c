/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ant_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 11:38:55 by lshanaha          #+#    #+#             */
/*   Updated: 2019/03/28 16:21:41 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/lem_in.h"
#include <unistd.h>

/*
** готовим массив для движения муравьев. размеры строк равны длине маршрутов
*/

int		**ft_array_for_lemmin_moves(int rou_count, int *rou_sizes)
{
	int		**zone;
	int		i;

	i = 0;
	zone = malloc(8 * rou_count);
	while (i < rou_count)
	{
		zone[i] = (int *)ft_memalloc(4 * rou_sizes[i] + 4);
		i++;
	}
	return (zone);
}

/*
** проверка - остались ли незакрытые маршруты
*/

int		ft_is_finished_all(int *start, int *end, int len)
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

/*
** перемещаем муравья и печатаем его движение на каждом шаге
*/

void	ft_lemmin_routine(t_routes *solved, int **zone, int k)
{
	int		i;
	int		j;

	i = (ROU_ANT_OFFSET[k] < ROU_SIZES[k])
			? (ROU_ANT_OFFSET[k])++ : ROU_ANT_OFFSET[k];
	(ROU_ANT_OFFSET[k] == ROU_SIZES[k]) ? ROU_ANT_FIN[k]++ : 0;
	j = 0;
	while (i > 0)
	{
		(ROU_ANT_OFFSET[k]) ? (zone[k][i] = zone[k][i - 1]) : 0;
		if (i < ROU_SIZES[k] && zone[k][i])
		{
			(k + j != 0) ? write(1, " ", 1) : 0;
			write(1, "L", 1);
			ft_putnbr(zone[k][i]);
			write(1, "-", 1);
			ft_putstr(ROU_ARR[k][i]);
			j++;
		}
		i--;
	}
	if (ROU_ANT_LEFT[k] == 0)
		zone[k][0] = 0;
}

/*
** k - is num of route.
*/

void	ft_lemmin_moves(t_routes *solved, int k, int num_of_ant_in_tube)
{
	int	**zone;

	zone = ft_array_for_lemmin_moves(ROU_NUM_WAYS, ROU_SIZES);
	while (ft_is_finished_all(ROU_ANT_NUM, ROU_ANT_FIN, ROU_NUM_WAYS))
	{
		if (ROU_ANT_NUM[k] != ROU_ANT_FIN[k])
		{
			ft_lemmin_routine(solved, zone, k);
			if (ROU_ANT_LEFT[k] > 0)
			{
				(num_of_ant_in_tube != 1) ? write(1, " ", 1) : 0;
				zone[k][0] = num_of_ant_in_tube++;
				write(1, "L", 1);
				ft_putnbr(zone[k][0]);
				write(1, "-", 1);
				ft_putstr(ROU_ARR[k][0]);
				ROU_ANT_LEFT[k]--;
			}
		}
		((k = (k + 1) % ROU_NUM_WAYS) == 0) ? ft_putchar('\n') : 0;
	}
	(k != 0) ? ft_putchar('\n') : 0;
	while (--ROU_NUM_WAYS >= 0)
		free(zone[ROU_NUM_WAYS]);
	free(zone);
}
