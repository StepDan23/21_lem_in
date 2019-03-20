/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solver.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 21:34:27 by lshanaha          #+#    #+#             */
/*   Updated: 2019/03/20 13:54:36 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

void		ft_go_further(t_lem_in *input)
{
	t_routes *solved;

	if (INP_START == -1 || INP_END == -1 || INP_MATRIX == 0)
	{
		free(input);
		ft_printf("ERROR IN ft_go_further\n");
		exit(ft_show_error());
	}
	solved = lem_routes(input);
	if ((!solved) || ROU_COUN <= 0)
		exit(ft_show_error_msg());
//Print
	ft_printf("|routes = %d|\n", ROU_COUN);
	int i;
	int j;
	i = 0;
	while (i < ROU_COUN)
	{
		j = 0;
		ft_printf("|size = %d|\n", ROU_SIZES[i]);
		while (j < ROU_SIZES[i])
			ft_printf("|%s| ", ROU_ARR[i][j++]);
		i++;
		ft_putendl("");
	}
	
//Print
//free t_routes
	i = 0;
	while (i < ROU_COUN)
	{
		ft_li_free_arr(ROU_ARR[i], ROU_SIZES[i]);
		i++;
	}
	free(ROU_ARR);
	free(ROU_SIZES);
	free(solved);
//free
	// ft_route_all_ants(solved);
}
