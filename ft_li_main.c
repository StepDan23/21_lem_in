/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_li_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 13:31:55 by lshanaha          #+#    #+#             */
/*   Updated: 2019/03/20 18:30:51 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>
#include <unistd.h>

int			ft_place_node_in_arr(t_lem_in *input, char *str)
{
	int	i;

	i = 0;
	while (i < INP_NODE_C)
	{
		if (!ft_strcmp(str, INP_NODES_NAMES[i]))
			return (i);
		i++;
	}
	return (-1);
}

void		ft_init_matrix(t_lem_in *input)
{
	char	**arr;
	int		i;
	int		j;

	(INP_NODE_C == 0) ? exit(ft_show_error()) : 0;
	arr = malloc(8 * INP_NODE_C);
	(!arr) ? (exit(ft_show_error_msg())) : 0;
	j = 0;
	while (j < INP_NODE_C)
	{
		arr[j] = malloc(INP_NODE_C + 1);
		if (!arr[j])
		{
			ft_li_free_arr(arr, j);
			exit(ft_show_error_msg());
		}
		i = 0;
		while (i < INP_NODE_C)
			arr[j][i++] = '0';
		arr[j][i] = 0;
		j++;
	}
	INP_MATRIX = arr;
}

void		ft_add_tube(t_lem_in *input, char *line, int *j)
{
	ft_printf("ft_add_tube\n");
	char	**arr;
	int		i;
	int		first;
	int		second;

	i = 0;
	(INP_MATRIX == 0) ? ft_init_matrix(input) : 0;
	(!(arr = ft_strsplit(line, '-'))) ? (exit(ft_show_error_msg())) : 0;
	while (arr[i])
		i++;
	if (i != 2)
	{
		ft_li_free_arr(arr, i);
		ft_go_further(input);
	}
	first = ft_place_node_in_arr(input, arr[0]);
	second = ft_place_node_in_arr(input, arr[1]);
	*j = 11;
	if (first < 0 || second < 0)
	{
		ft_li_free_arr(arr, i);
		return ;
	}
	INP_MATRIX[first][second] = '1';
	INP_MATRIX[second][first] = '1';
	ft_li_free_arr(arr, i);
}

int			main(void)
{
	char		*line;
	t_lem_in	*input;
	int			j;

	j = 0;
	input = ft_input_init();
	while (get_next_line(0, &line) > 0)
	{
		(line[0] != '#' && j >= 10 && j <= 20) ? (ft_add_tube(input, line, &j)) : 0;
		(line[0] != '#' && j > 0 && j < 10) ? (ft_add_node(input, line, &j)) : 0;
		(j == 0) ? (ft_ant_count(input, line, &j)) : 0;
		(j & (1 << 14)) ? (ft_li_end(input, line, &j)) : 0;
		(j & (1 << 15)) ? (ft_li_start(input, line, &j)) : 0;
		(line[0] == '#' && j >= 0 && j < 10) ? (ft_li_comment(input, line, &j)) : 0;
		ft_putendl(line);
		free(line);
	}
	ft_printf("start = %s, end = %s\n", INP_NODES_NAMES[INP_START], INP_NODES_NAMES[INP_END]);
	for (int i = 0; i < INP_NODE_C; i++)
		ft_printf("node = %s\n", INP_NODES_NAMES[i]);
	(j) ? (free(line)) : 0;
	ft_go_further(input);
	return (1);
}
