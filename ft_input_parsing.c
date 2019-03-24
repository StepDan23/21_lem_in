/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 13:28:05 by lshanaha          #+#    #+#             */
/*   Updated: 2019/03/24 18:22:22 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		ft_ant_count(t_lem_in *input, char *line, int *j)
{
	int		res;

	if (ft_num_isdigit(line))
		exit(ft_show_error());
	res = ft_atoi(line);
	if (ft_atol(line) != res)
		exit(ft_show_error());
	INP_ANT_C = res;
	if (res <= 0 || INP_ANT_C <= 0)
		exit(ft_show_error());
	*j = 1;
}

void		ft_li_comment(t_lem_in *input, char *line, int *j)
{
	if (line[1] == '#')
	{
		if (*j >= 10 && *j <= 20)
		{
			free(line);
			ft_go_further(input);
		}
		if (!ft_strcmp(&(line[2]), "start"))
			*j = 1 << 15;
		else if (!ft_strcmp(&(line[2]), "end"))
			*j = 1 << 14;
		return ;
	}
	if (!ft_strcmp(&(line[1]), "stone"))
		*j = 1 << 16;
}

void		ft_li_start(t_lem_in *input, char *line, int *j)
{
	char	**arr;
	int		i;

	arr = ft_strsplit(line, ' ');
	i = 0;
	while (arr[i])
		i++;
	if (i != 3 || ft_num_isdigit(arr[1]) || ft_num_isdigit(arr[2]) ||\
	arr[0][0] == 'L' || ft_place_node_in_arr(input, arr[0]) >= 0)
	{
		free(line);
		ft_li_free_arr(arr, i);
		ft_go_further(input);
	}
	INP_NODES_NAMES[INP_NODE_C] = ft_strdup(arr[0]);
	INP_NODES_XS[INP_NODE_C] = ft_strdup(arr[1]);
	INP_NODES_YS[INP_NODE_C] = ft_strdup(arr[2]);
	INP_START = INP_NODE_C;
	INP_NODE_C++;
	ft_li_free_arr(arr, i);
	*j = 1;
}

void		ft_li_end(t_lem_in *input, char *line, int *j)
{
	char	**arr;
	int		i;

	arr = ft_strsplit(line, ' ');
	i = 0;
	while (arr[i])
		i++;
	if (i != 3 || ft_num_isdigit(arr[1]) || ft_num_isdigit(arr[2]) ||\
	arr[0][0] == 'L' || ft_place_node_in_arr(input, arr[0]) >= 0)
	{
		free(line);
		ft_li_free_arr(arr, i);
		ft_go_further(input);
	}
	INP_NODES_NAMES[INP_NODE_C] = ft_strdup(arr[0]);
	INP_NODES_XS[INP_NODE_C] = ft_strdup(arr[1]);
	INP_NODES_YS[INP_NODE_C] = ft_strdup(arr[2]);
	INP_END = INP_NODE_C;
	INP_NODE_C++;
	ft_li_free_arr(arr, i);
	*j = 1;
}

void		ft_node(t_lem_in *input, char *line, int *j, int i)
{
	char	**arr;

	(INP_NODE_C == 9998) ? (exit(ft_show_error())) : 0;
	arr = ft_strsplit(line, ' ');
	while (arr[i])
		i++;
	if (i == 1)
	{
		ft_li_free_arr(arr, i);
		ft_tube(input, line, j);
		return ;
	}
	if (i != 3 || ft_num_isdigit(arr[1]) || ft_num_isdigit(arr[2]) ||\
	arr[0][0] == 'L' || ft_place_node_in_arr(input, arr[0]) >= 0)
	{
		free(line);
		ft_li_free_arr(arr, i);
		ft_go_further(input);
	}
	INP_NODES_NAMES[INP_NODE_C] = ft_strdup(arr[0]);
	INP_NODES_XS[INP_NODE_C] = ft_strdup(arr[1]);
	INP_NODES_YS[INP_NODE_C] = ft_strdup(arr[2]);
	INP_NODE_C++;
	ft_li_free_arr(arr, i);
	*j = 1;
}
