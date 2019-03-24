/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_li_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 13:31:55 by lshanaha          #+#    #+#             */
/*   Updated: 2019/03/24 18:45:39 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>
#include <unistd.h>

/*
** Проверяем, встречался ли узел с таким именем ранее
*/
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

int			ft_stone_check(t_lem_in *input, char *str1, char *str2)
{
	int	i;

	i = 0;
	while (i < INP_STONES_C)
	{
		if (!ft_strcmp(str1, INP_STONES[i]))
			return (1);
		if (!ft_strcmp(str2, INP_STONES[i]))
			return (1);
		i++;
	}
	return (0);
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

void		ft_tube(t_lem_in *input, char *line, int *j)
{
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
	*j = 11;
	first = ft_place_node_in_arr(input, arr[0]);
	second = ft_place_node_in_arr(input, arr[1]);
	if (first < 0 || second < 0 || ft_stone_check(input, arr[0], arr[1]))
		i = -10;
	ft_li_free_arr(arr, i);
	(i != -10) ? INP_MATRIX[first][second] = '1' : 0;
	(i != -10) ? INP_MATRIX[second][first] = '1' : 0;
}

void		ft_stone(t_lem_in *input, char *line, int *j)
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
	if (!INP_STONES)
		INP_STONES = ft_memalloc(8 * 10000);
	INP_STONES[INP_STONES_C++] = ft_strdup(arr[0]);
	INP_NODES_NAMES[INP_NODE_C] = ft_strdup(arr[0]);
	INP_NODES_XS[INP_NODE_C] = ft_strdup(arr[1]);
	INP_NODES_YS[INP_NODE_C] = ft_strdup(arr[2]);
	INP_NODE_C++;
	ft_li_free_arr(arr, i);
	*j = 1;
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
		(line[0] != '#' && j >= 10 && j <= 20) ? (ft_tube(input, line, &j)) : 0;
		(line[0] != '#' && j > 0 && j < 10) ? (ft_node(input, line, &j, 0)) : 0;
		(j == 0) ? (ft_ant_count(input, line, &j)) : 0;
		(line[0] != '#' && j & (1 << 14)) ? (ft_li_end(input, line, &j)) : 0;
		(line[0] != '#' && j & (1 << 15)) ? (ft_li_start(input, line, &j)) : 0;
		(line[0] != '#' && j & (1 << 16)) ? (ft_stone(input, line, &j)) : 0;
		(line[0] == '#') ? (ft_li_comment(input, line, &j)) : 0;
		ft_putendl(line);
		free(line);
	}
	(j) ? (free(line)) : 0;
	ft_go_further(input);
	return (0);
}
