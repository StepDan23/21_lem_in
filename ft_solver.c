/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solver.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 21:34:27 by lshanaha          #+#    #+#             */
/*   Updated: 2019/03/19 11:55:31 by mmcclure         ###   ########.fr       */
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
}
