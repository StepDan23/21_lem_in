/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solver.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 21:34:27 by lshanaha          #+#    #+#             */
/*   Updated: 2019/03/23 13:22:11 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

void	ft_go_further(t_lem_in *input)
{
	t_routes	*solved;
	int			i;

	if (INP_START == -1 || INP_END == -1 || INP_MATRIX == 0)
	{
		free(input);
		exit(ft_show_error());
	}
	solved = lem_routes(input);
	if ((!solved) || ROU_COUN <= 0)
		exit(ft_show_error_msg());
	ft_route_all_ants(solved, -1);
	i = -1;
	while (++i < ROU_COUN)
		ft_li_free_arr(ROU_ARR[i], ROU_SIZES[i]);
	free(ROU_ARR);
	free(ROU_SIZES);
	free(solved);
	exit(0);
}

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

void	ft_route_all_ants(t_routes *solved, int i)
{
	ft_num_of_ants_in_path(solved, 0, ROU_ANT_C, ft_memalloc(4 * ROU_COUN));
	i = -1;
	while (++i < ROU_COUN && ROU_ANT_NUM[i])
		;
	ROU_NUM_WAYS = i;
	ROU_ANT_FIN = ft_memalloc(4 * ROU_NUM_WAYS);
	ROU_ANT_OFFSET = ft_memalloc(4 * ROU_NUM_WAYS);
	ROU_ANT_LEFT = malloc(4 * ROU_NUM_WAYS);
	i = -1;
	while (++i < ROU_NUM_WAYS)
		ROU_ANT_LEFT[i] = ROU_ANT_NUM[i];
	ft_lemmin_moves(solved, 0, 0, 1);
	free(ROU_ANT_FIN);
	free(ROU_ANT_OFFSET);
	free(ROU_ANT_LEFT);
	free(ROU_ANT_NUM);
}
