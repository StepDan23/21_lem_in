/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 21:15:17 by lshanaha          #+#    #+#             */
/*   Updated: 2019/03/20 19:13:49 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		ft_ant_count(t_lem_in *input, char *line, int *j)
{
	int		res;

	ft_printf("add count\n");
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
		if (*j > 10)
		{
			free(line);
			ft_printf("ERROR IN ft_li_comment\n");
			ft_go_further(input);
		}
		if (!ft_strcmp(&(line[2]), "start"))
			*j = 1 << 15;
		else if (!ft_strcmp(&(line[2]), "end"))
			*j = 1 << 14;
	}
}

void		ft_li_start(t_lem_in *input, char *line, int *j)
{
	char	**arr;
	int		i;

	ft_printf("ft_li_start\n");
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

	ft_printf("ft_li_end\n");
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

void		ft_add_node(t_lem_in *input, char *line, int *j, int i)
{
	char	**arr;

	ft_printf("ft_add_node\n");
	arr = ft_strsplit(line, ' ');
	while (arr[i])
		i++;
	if (i == 1)
	{
		ft_li_free_arr(arr, i);
		ft_add_tube(input, line, j);
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
