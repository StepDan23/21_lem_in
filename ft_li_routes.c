/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_li_routes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 13:55:58 by mmcclure          #+#    #+#             */
/*   Updated: 2019/03/19 19:18:56 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		lem_del_node(t_lem_in *input, int *route)
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

static void		lem_fill_route(t_lem_in *input, t_routes *solved, int *route)
{
	int		word;

	ROU_SIZES[ROU_COUN] = 0;
	word = 0;
	while (route[ROU_SIZES[ROU_COUN]] != -1)
		ROU_SIZES[ROU_COUN]++;
	if (!(ROU_ARR[ROU_COUN] =
			(char**)malloc(sizeof(char*) * (ROU_SIZES[ROU_COUN] + 1))))
		return ;
	while (word < ROU_SIZES[ROU_COUN])
	{
		ROU_ARR[ROU_COUN][word] = ft_strdup(INP_NODES_NAMES[route[word]]);
		word++;
	}
	ROU_ARR[ROU_COUN][word] = NULL;
}

static int		*lem_make_route(t_lem_in *input, int *bgf)
{
	int		*route;
	int		dst;
	int		i;

	dst = bgf[INP_END];
	if (!(route = lem_intnew(dst)))
		return (NULL);
	route[--dst] = INP_END;
	while (dst > 0)
	{
		i = 0;
		while (INP_MATRIX[route[dst]][i] != '\0')
		{
			if (INP_MATRIX[route[dst]][i] == '1' && bgf[i] == dst)
			{
				route[--dst] = i;
				break ;
			}
			i++;
		}
	}
	return (route);
}

static int		*lem_bgf(t_lem_in *input)
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

t_routes		*lem_routes(t_lem_in *input)
{
	t_routes	*solved;
	int			*bgf;
	int			*route;

	if (!(solved = rou_init(input)))
		return (NULL);
	while (ROU_COUN < INP_NODE_C - 1)
	{
		bgf = lem_bgf(input);
		if (!(route = lem_make_route(input, bgf)))
		{
			free(bgf);
			break ;
		}
		lem_fill_route(input, solved, route);
		lem_del_node(input, route);
		free(route);
		free(bgf);
		ROU_COUN++;
	}
	ROU_ARR[ROU_COUN] = NULL;
	lem_free_tlem(input);
	return (solved);
}
