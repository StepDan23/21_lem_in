/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_li_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 13:31:55 by lshanaha          #+#    #+#             */
/*   Updated: 2019/03/17 15:17:05 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

char		ft_show_error_msg(void)
{
	ft_putstr("Some error oqqured\n");
	return (1);
}

char		ft_show_error(void)
{
	ft_putstr("ERROR\n");
	return (1);
}

void		ft_li_free_arr(char **arr, int i)
{
	int		j;

	j = 0;
	while (j < i)
	{
		free(arr[j]);
		j++;
	}
	free(arr);
}

int			ft_num_isdigit(char *num)
{
	int	i;

	i = 0;
	while (num[i] == ' ' || num[i] == '\t')
		i++;
	if (num[i] == '-' || num[i] == '+')
		i++;
	while (num[i])
	{
		if (num[i] < '0' || num[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

t_lem_in	*ft_input_init(void)
{
	t_lem_in	*input;

	input = malloc(sizeof(t_lem_in));
	INP_NODES = malloc(8 * 3);
	INP_NODES_NAMES = malloc(8 * 10000);
	INP_NODES_XS = malloc(8 * 10000);
	INP_NODES_YS = malloc(8 * 10000);
	INP_ANT_C = 0;
	INP_START = 0;
	INP_END = 0;
	INP_NODE_C = 0;
	INP_MATRIX = NULL;
	return (input);
}

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
	if (res < 0)
		exit(ft_show_error());
	*j = 1;
}

void		ft_li_comment(t_lem_in *input, char *line, int *j)
{
	if (line[1] == '#')
	{
		if (*j > 10)
			exit(ft_show_error());
		if (!ft_strcmp(&(line[2]), "start"))
			*j = 1 << 15;
		else if (!ft_strcmp(&(line[2]), "end"))
			*j = 1 << 14;
		else
			exit(ft_show_error());
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
	if (i != 3)
		exit(ft_show_error());
	if (ft_num_isdigit(arr[1]) || ft_num_isdigit(arr[2]))
		exit(ft_show_error());
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
	if (i != 3)
		exit(ft_show_error());
	if (ft_num_isdigit(arr[1]) || ft_num_isdigit(arr[2]))
		exit(ft_show_error());
	INP_NODES_NAMES[INP_NODE_C] = ft_strdup(arr[0]);
	INP_NODES_XS[INP_NODE_C] = ft_strdup(arr[1]);
	INP_NODES_YS[INP_NODE_C] = ft_strdup(arr[2]);
	INP_END = INP_NODE_C;
	INP_NODE_C++;
	free(arr[2]);
	free(arr[1]);
	free(arr[0]);
	free(arr);
	*j = 1;
}

void		ft_init_matrix(t_lem_in *input)
{
	char	**arr;
	int		i;
	int		j;

	(INP_NODE_C == 0) ? exit(ft_show_error()) : 0;
	arr = malloc(8 * INP_NODE_C);
	(!arr) ? (ft_show_error_msg()) : 0;
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

int			ft_place_in_arr(t_lem_in *input, char *str)
{
	int	i;

	i = 0;
	while (i < INP_NODE_C)
	{
		if (!ft_strcmp(str, INP_NODES_NAMES[i]))
			return (i);
		i++;
	}
	//exit(ft_show_error());
	return (-1);
}

void		ft_add_tube(t_lem_in *input, char *line, int *j)
{
	ft_printf("ft_add_tube\n");
	char	**arr;
	int		i;
	int		first;
	int		second;

	(INP_MATRIX == 0) ? ft_init_matrix(input) : 0;
	arr = ft_strsplit(line, '-');
	while (arr[i])
		i++;
	(i != 2) ? exit(ft_show_error()) : 0;
	first = ft_place_in_arr(input, arr[0]);
	second = ft_place_in_arr(input, arr[1]);
	if (first < 0 || second < 0)
	{
		*j = 11;
		return ;	
	}
	INP_MATRIX[first][second] = '1';
	INP_MATRIX[second][first] = '1';
	ft_li_free_arr(arr, i);
	*j = 11;
}

void		ft_add_node(t_lem_in *input, char *line, int *j)
{
	char	**arr;
	int		i;

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
	(i != 3) ? exit(ft_show_error()) : 0;
	if (ft_num_isdigit(arr[1]) || ft_num_isdigit(arr[2]))
		exit(ft_show_error());
	INP_NODES_NAMES[INP_NODE_C] = ft_strdup(arr[0]);
	INP_NODES_XS[INP_NODE_C] = ft_strdup(arr[1]);
	INP_NODES_YS[INP_NODE_C] = ft_strdup(arr[2]);
	INP_NODE_C++;
	ft_li_free_arr(arr, i);
	*j = 1;
}


//нужно ли проверять что поданы одинаковые узлы,
// Нужно ли проверять что в тьюбах поданы существующие узлы
int			main(void)
{
	char		*line;
	char		**arr;
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
		free(line);
	}
	ft_printf("start = %s, end = %s\n", INP_NODES_NAMES[INP_START], INP_NODES_NAMES[INP_END]);
	for (int i = 0; i < INP_NODE_C; i++)
		ft_printf("node = %s\n", INP_NODES_NAMES[i]);
	for (int i = 0; i < INP_NODE_C; i++)
	{
		ft_printf("%s\n", INP_MATRIX[i]);
	}
	(j) ? (free(line)) : 0;
	return (1);
}
