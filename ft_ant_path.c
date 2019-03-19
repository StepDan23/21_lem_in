/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ant_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 11:38:55 by lshanaha          #+#    #+#             */
/*   Updated: 2019/03/19 12:40:01 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_num_of_ants_in_path(t_routes *solved)
{
	int		*arr;
	int		quant;
	int		temp;
	int		i;

	quant = 0;
	temp = 0;
	arr = (int *)malloc((ROU_COUN + 1) * 4);
	(!arr) ? (exit(ft_show_error_msg())) : 0;
	while (i < ROU_COUN)
		temp += ROU_SIZES[i];
	ft_printf("temp = %d, quant = %d\n", temp, quant);
	quant = (int)(ROU_ANT_C / temp);
	i = 0;
	temp = 0;
	while (i < ROU_COUN)
	{
		arr[i] = quant * ROU_SIZES[i];
		(i < ROU_COUN - 1) ? temp += arr[i] : 0;
		(i == ROU_COUN - 1) ? (arr[i] = ROU_ANT_C - temp) : 0;
		i++;
	}
	ft_int_arr_rev(arr, i);
	for (i = 0; i < ROU_COUN; i++)
		ft_printf("| %d ", arr[i]);
	ft_printf("|\n");
}

void	ft_route_all_ants(t_routes *solved)
{
	ft_printf("come to solve!\n");
	ft_printf("ant count = %d, num of ways = %d\n", ROU_ANT_C, ROU_COUN);
	for (int i = 0; i < ROU_COUN; i++)
		ft_printf("| %d ", ROU_SIZES[i]);
	ft_printf("|\n");
	ft_num_of_ants_in_path(solved);
}
