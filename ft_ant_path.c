/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ant_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how_r_u <how_r_u@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 11:38:55 by lshanaha          #+#    #+#             */
/*   Updated: 2019/03/23 00:18:55 by how_r_u          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** arrs- it's a count of ants in each tube. rations - substraction of each len
** and len of first tube (first tube also included);
*/
void	ft_num_of_ants_in_path(t_routes *solved, int i, int temp, int *rations)
{
	int		*arrs;

	arrs = (int *)ft_memalloc(4 * ROU_COUN);
	(!rations || !arrs) ? exit(ft_show_error_msg()) : (ROU_ANT_NUM = arrs);
	while (++i < ROU_COUN)
	{
		rations[i] = ROU_SIZES[i] - ROU_SIZES[0];
		arrs[i] = rations[i];
	}
	while (temp > 0)
	{
		arrs[0]++;
		temp--;
		i = -1;
		while (++i + 1 < ROU_COUN && (arrs[i] > arrs[i + 1]) && temp > 0)
		{
			arrs[i + 1]++;
			temp--;
		}
	}
	i = -1;
	while (++i < ROU_COUN)
		arrs[i] -= rations[i];
	free(rations);
}

int		**ft_array_for_lemmin_moves(int rou_count, int *rou_sizes)
{
	int		**zone;
	int		i;

	i = 0;
	zone = malloc(8 * rou_count);
	while (i < rou_count)
	{
		zone[i] = (int *)malloc(4 * rou_sizes[i] + 4);
		i++;
	}
	return (zone);
}

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

/*
** k - is num of route.
*/
void	ft_lemmin_moves(t_routes *solved, int i, int k, int num_of_ant_in_tube)
{
	int	**zone;

	zone = ft_array_for_lemmin_moves(ROU_NUM_WAYS, ROU_SIZES);
	while (ft_is_finished_all(ROU_ANT_NUM, ROU_ANT_FIN, ROU_NUM_WAYS))
	{
		if (ROU_ANT_NUM[k] != ROU_ANT_FIN[k])
		{

			i = (ROU_ANT_OFFSET[k] < ROU_SIZES[k]) ? ROU_ANT_OFFSET[k]++ : ROU_ANT_OFFSET[k];
			(ROU_ANT_OFFSET[k] == ROU_SIZES[k]) ? ROU_ANT_FIN[k]++ : 0;
			while (i > 0)
			{
				(ROU_ANT_OFFSET[k]) ? (zone[k][i] = zone[k][i - 1]) : 0;
				(i < ROU_SIZES[k] && zone[k][i]) ? ft_printf("L%d-%s ", zone[k][i], ROU_ARR[k][i]) : 0;
				i--;
			}
			if (ROU_ANT_LEFT[k] == 0)
				zone[k][0] = 0;
			if (ROU_ANT_LEFT[k] > 0)
			{
				zone[k][0] = num_of_ant_in_tube;
				num_of_ant_in_tube++;
				ROU_ANT_LEFT[k]--;
			}
		}
		k = (k + 1) % ROU_NUM_WAYS;
		(k == 0 && ROU_ANT_OFFSET[ROU_NUM_WAYS - 1] > 1) ? ft_putchar('\n') : 0;
	}
	(k != 0) ? ft_putchar('\n') : 0;
	while (--ROU_NUM_WAYS >= 0)
		free(zone[ROU_NUM_WAYS]);
	free(zone);
	//free(solved);
}

void	ft_route_all_ants(t_routes *solved, int i)
{
	ft_num_of_ants_in_path(solved, 0, ROU_ANT_C, ft_memalloc(4 * ROU_COUN));
	for (i = 0; i < ROU_COUN; i++)
		ft_printf("| %d ", ROU_ANT_NUM[i]);
	ft_putstr("|\n");
	i = -1;
	while (++i < ROU_COUN && ROU_ANT_NUM[i])
		;
	ft_printf("i = %d\n", i);
	ROU_NUM_WAYS = i;
	ROU_ANT_FIN = ft_memalloc(4 * ROU_NUM_WAYS);
	ROU_ANT_OFFSET = ft_memalloc(4 * ROU_NUM_WAYS);
	ROU_ANT_LEFT = malloc(4 * ROU_NUM_WAYS);
	i = -1;
	while (++i < ROU_NUM_WAYS)
		ROU_ANT_LEFT[i] = ROU_ANT_NUM[i];
	// ft_putstr("\nfin: \n");
	// for (i = 0; i < ROU_NUM_WAYS; i++)
	// 	ft_printf("%d ", ROU_ANT_FIN[i]);
	// ft_putstr("\nleft: \n");
	// for (i = 0; i < ROU_NUM_WAYS; i++)
	// 	ft_printf("%d ", ROU_ANT_LEFT[i]);
	// ft_putstr("\noffset: \n");
	// for (i = 0; i < ROU_NUM_WAYS; i++)
	// 	ft_printf("%d ", ROU_ANT_OFFSET[i]);
	// ft_putchar('\n');
	ft_lemmin_moves(solved, 0, 0, 1);
	free(ROU_ANT_FIN);
	free(ROU_ANT_OFFSET);
	free(ROU_ANT_LEFT);
	free(ROU_ANT_NUM);
}
