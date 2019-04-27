/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_parsing_collect_data.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 18:11:08 by lshanaha          #+#    #+#             */
/*   Updated: 2019/03/28 13:32:37 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/visu.h"
#include <stdlib.h>

void		ft_li_start(t_visual *parse, char *line, int *j)
{
	char	**arr;
	int		i;

	arr = ft_strsplit(line, ' ');
	i = 0;
	while (arr[i])
		i++;
	NAME[SIZE] = ft_strdup(arr[0]);
	COORD[SIZE][0] = ft_atoi(arr[1]);
	COORD[SIZE][1] = ft_atoi(arr[2]);
	(COORD[SIZE][1] > Y_MAX) ? Y_MAX = COORD[SIZE][1] : 0;
	(COORD[SIZE][1] < Y_MIN) ? Y_MIN = COORD[SIZE][1] : 0;
	(COORD[SIZE][0] > X_MAX) ? X_MAX = COORD[SIZE][0] : 0;
	(COORD[SIZE][0] < X_MIN) ? X_MIN = COORD[SIZE][0] : 0;
	START = SIZE;
	SIZE = SIZE + 1;
	ft_li_free_char_arr(arr, i);
	*j = 1;
}

void		ft_li_end(t_visual *parse, char *line, int *j)
{
	char	**arr;
	int		i;

	arr = ft_strsplit(line, ' ');
	i = 0;
	while (arr[i])
		i++;
	NAME[SIZE] = ft_strdup(arr[0]);
	COORD[SIZE][0] = ft_atoi(arr[1]);
	COORD[SIZE][1] = ft_atoi(arr[2]);
	(COORD[SIZE][1] > Y_MAX) ? Y_MAX = COORD[SIZE][1] : 0;
	(COORD[SIZE][1] < Y_MIN) ? Y_MIN = COORD[SIZE][1] : 0;
	(COORD[SIZE][0] > X_MAX) ? X_MAX = COORD[SIZE][0] : 0;
	(COORD[SIZE][0] < X_MIN) ? X_MIN = COORD[SIZE][0] : 0;
	END = SIZE;
	SIZE++;
	ft_li_free_char_arr(arr, i);
	*j = 1;
}

void		ft_node(t_visual *parse, char *line, int *j, int i)
{
	char	**arr;

	arr = ft_strsplit(line, ' ');
	while (arr[i])
		i++;
	if (i == 1)
	{
		ft_li_free_char_arr(arr, i);
		ft_tube(parse, line, j);
		return ;
	}
	NAME[SIZE] = ft_strdup(arr[0]);
	COORD[SIZE][0] = ft_atoi(arr[1]);
	COORD[SIZE][1] = ft_atoi(arr[2]);
	(COORD[SIZE][1] > Y_MAX) ? Y_MAX = COORD[SIZE][1] : 0;
	(COORD[SIZE][1] < Y_MIN) ? Y_MIN = COORD[SIZE][1] : 0;
	(COORD[SIZE][0] > X_MAX) ? X_MAX = COORD[SIZE][0] : 0;
	(COORD[SIZE][0] < X_MIN) ? X_MIN = COORD[SIZE][0] : 0;
	SIZE++;
	ft_li_free_char_arr(arr, i);
	*j = 1;
}

void		ft_tube(t_visual *parse, char *line, int *j)
{
	char	**arr;
	int		i;
	int		first;
	int		second;

	i = 0;
	(MATRIX == 0) ? ft_init_matrix(parse) : 0;
	(!(arr = ft_strsplit(line, '-'))) ? (exit(ft_show_error())) : 0;
	while (arr[i])
		i++;
	first = ft_place_node_in_arr(parse, arr[0]);
	second = ft_place_node_in_arr(parse, arr[1]);
	*j = 11;
	ft_li_free_char_arr(arr, i);
	if (first < 0 || second < 0)
		return ;
	MATRIX[first][second] = '1';
	MATRIX[second][first] = '1';
}

void		ft_li_comment(char *line, int *j)
{
	if (line[1] == '#')
	{
		if (!ft_strcmp(&(line[2]), "start"))
			*j = 1 << 15;
		else if (!ft_strcmp(&(line[2]), "end"))
			*j = 1 << 14;
	}
}
