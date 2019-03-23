/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_li_routes_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 13:25:01 by lshanaha          #+#    #+#             */
/*   Updated: 2019/03/23 13:25:02 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_routes	*rou_init(t_lem_in *input)
{
	t_routes	*solved;

	if (!(solved = (t_routes*)malloc(sizeof(t_routes))))
		return (NULL);
	ROU_ANT_C = INP_ANT_C;
	ROU_COUN = 0;
	ROU_ARR = (char***)malloc(sizeof(char**) * INP_NODE_C);
	ROU_SIZES = lem_intnew(INP_NODE_C);
	if (!ROU_ARR || !ROU_SIZES)
		return (NULL);
	return (solved);
}

int			lem_intcmp(int *line, int j, int size)
{
	while (size--)
	{
		if (*line == j)
			return (1);
		line += 1;
	}
	return (0);
}

int			*lem_intnew(int size)
{
	int		*new;

	if (size <= 0)
		return (NULL);
	if (!(new = (int*)malloc(sizeof(int) * (size + 1))))
		return (NULL);
	while (size >= 0)
	{
		new[size] = -1;
		size--;
	}
	return (new);
}

void		lem_free_tlem(t_lem_in *input)
{
	ft_li_free_arr(INP_MATRIX, INP_NODE_C);
	ft_li_free_arr(INP_NODES_NAMES, INP_NODE_C);
	ft_li_free_arr(INP_NODES_XS, INP_NODE_C);
	ft_li_free_arr(INP_NODES_YS, INP_NODE_C);
	free(INP_NODES);
	free(input);
}
