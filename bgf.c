/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bgf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 13:55:58 by mmcclure          #+#    #+#             */
/*   Updated: 2019/03/19 11:54:21 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		lem_intcmp(int *line, int j, int size)
{
	while (size--)
	{
		if (*line == j)
			return (1);
		line += 1;
	}
	return (0);
}

static int		*lem_intnew(int size)
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

int				*lem_make_route(t_lem_in *input, int *bgf)
{
	int		*route;
	int		dst;
	int		i;

	dst = bgf[INP_END];
	if (!(route = lem_intnew(dst + 1)))
		return (NULL);
	route[dst] = INP_END;
	while (dst > 0)
	{
		i = 0;
		while (INP_MATRIX[route[dst]][i] != '\0')
		{
			if (INP_MATRIX[route[dst]][i] == '1' && bgf[i] == dst - 1)
			{
				route[--dst] = i;
				break ;
			}
			i++;
		}
	}
	return (route);
}

int				*lem_bgf(t_lem_in *input)
{
	int		*line;
	int		*out;
	int		i;
	int		j;
	int		k;

	if (!(out = lem_intnew(INP_NODE_C)) ||
				!(line = lem_intnew(INP_NODE_C)))
		return (NULL);
	i = 0;
	k = 1;
	line[0] = INP_START;
	out[INP_START] = 0;
	while (line[i] != -1)
	{
		j = 0;
		while (INP_MATRIX[line[i]][j] != '\0')
		{
			if (INP_MATRIX[line[i]][j] == '1' && !lem_intcmp(line, j, INP_NODE_C))
			{
				line[k++] = j;
				out[j] = out[line[i]] + 1;
			}
			j++;
		}
		i++;
	}
	free(line);
	return (out);
}

void			lem_del_node(t_lem_in *input, int *route)
{
	int		i;
	int		j;

	if (!route)
		return ;
	i = 0;
	INP_MATRIX[INP_END][INP_START] = '0';
	INP_MATRIX[INP_START][INP_END] = '0';
	while (route[i] != -1)
	{
		if (route[i] != INP_START && route[i] != INP_END)
		{
			j = 0;
			while (j < INP_NODE_C)
			{
				INP_MATRIX[j][route[i]] = '0';
				j++;
			}
			ft_memset(INP_MATRIX[route[i]], '0', INP_NODE_C);
		}
		i++;
	}
}

t_routes		*lem_routes(t_lem_in *input)
{
	t_routes	*solved;
	int			*bgf;

	solved = (t_routes*)malloc(sizeof(t_routes));
	ROU_ARR = (int**)malloc(sizeof(int*) * INP_NODE_C);
	ROU_SIZES = lem_intnew(INP_NODE_C);
	ROU_ANT_C = INP_ANT_C;
	ROU_COUN = 0;
	while (ROU_COUN < INP_NODE_C - 1)
	{
		bgf = lem_bgf(input);
		ROU_SIZES[ROU_COUN] = 0;
		if (!(ROU_ARR[ROU_COUN] = lem_make_route(input, bgf)))
		{
			free(bgf);
			break ;
		}
		while (ROU_ARR[ROU_COUN][ROU_SIZES[ROU_COUN]] != -1)
			ROU_SIZES[ROU_COUN] += 1;
		lem_del_node(input, ROU_ARR[ROU_COUN]);
		free(bgf);
		ROU_COUN++;
	}
	ROU_ARR[ROU_COUN] = NULL;
	return (solved);
}
