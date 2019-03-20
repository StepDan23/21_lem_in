/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ant_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 11:38:55 by lshanaha          #+#    #+#             */
/*   Updated: 2019/03/20 21:29:32 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_num_of_ants_in_path(t_routes *solved, int i, int temp)
{
	int		*rations;
	int		*arrs;

	rations = (int *)ft_memalloc(4 * ROU_COUN);
	arrs = (int *)ft_memalloc(4 * ROU_COUN);
	if (!rations || !arrs)
		exit(ft_show_error_msg());
	while (++i < ROU_COUN)
		rations[i] = ROU_SIZES[i] - ROU_SIZES[0];
	while (temp > 0)
	{
		arrs[0]++;
		temp--;
		i = -1;
		while (++i + 1 < ROU_COUN && (rations[i] + arrs[i] > arrs[i + 1] +\
		rations[i + 1]) && temp > 0)
		{
			arrs[i + 1]++;
			temp--;
		}
	}
	free(rations);
	ROU_ANT_NUM = arrs;
}

void	ft_route_all_ants(t_routes *solved, int i)
{
	ft_num_of_ants_in_path(solved, 0, ROU_ANT_C);
	for (i = 0; i < ROU_COUN; i++)
		ft_printf("| %d ", ROU_ANT_NUM[i]);
	ft_putstr("|\n");
	i = -1;
	while (++i < ROU_COUN && ROU_ANT_NUM[i])
		;
	ft_printf("i = %d\n", i);
	ROU_NUM_WAYS = i;
}
