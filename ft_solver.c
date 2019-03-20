/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solver.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 21:34:27 by lshanaha          #+#    #+#             */
/*   Updated: 2019/03/20 21:11:29 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

void		ft_go_further(t_lem_in *input)
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
	ft_printf("|routes = %d|\n", ROU_COUN);
	i = 0;
	while (i < ROU_COUN)
		ft_printf("| %d ", ROU_SIZES[i++]);
	ft_putstr("|\n");
	ft_route_all_ants(solved, -1);
	i = -1;
	while (++i < ROU_COUN)
		ft_li_free_arr(ROU_ARR[i], ROU_SIZES[i]);
	free(ROU_ARR);
	free(ROU_SIZES);
	free(solved);
	exit(0);
}
