/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 14:23:22 by lshanaha          #+#    #+#             */
/*   Updated: 2019/03/23 18:40:24 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "visual.h"

int		ft_show_error(void)
{
	ft_putstr_fd("ERROR\n", 2);
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

t_visual	*ft_init_parse(void)
{
	t_visual	*parse;
	int			i;

	i = 0;
	parse = malloc(sizeof(t_visual));
	if (!parse)
		exit(ft_show_error());
	NAME = malloc(8 * 10000);
	COORD = malloc(8 * 10000);
	while (i < 10000)
		COORD[i++] = (int *)malloc(8);
	SIZE = 0;
	X_RAT = 1;
	Y_RAT = 1;
	MATRIX = NULL;
	X_MAX = -1;
	Y_MAX = -1;
	X_MIN = 2000000000;
	Y_MIN = 2000000000;
	return (parse);
}

int			ft_place_node_in_arr(t_visual *parse, char *str)
{
	int	i;

	i = 0;
	while (i < SIZE)
	{
		if (!ft_strcmp(str, NAME[i]))
			return (i);
		i++;
	}
	return (-1);
}

void		ft_init_matrix(t_visual *parse)
{
	char	**arr;
	int		i;
	int		j;

	arr = malloc(8 * SIZE);
	(!arr) ? (exit(ft_show_error())) : 0;
	j = 0;
	while (j < SIZE)
	{
		arr[j] = malloc(SIZE + 1);
		if (!arr[j])
		{
			ft_li_free_arr(arr, j);
			exit(ft_show_error());
		}
		i = 0;
		while (i < SIZE)
			arr[j][i++] = '0';
		arr[j][i] = 0;
		j++;
	}
	MATRIX = arr;
}

void		ft_add_tube(t_visual *parse, char *line, int *j)
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
	ft_li_free_arr(arr, i);
	if (first < 0 || second < 0)
		return ;
	MATRIX[first][second] = '1';
	MATRIX[second][first] = '1';

}

void		ft_add_node(t_visual *parse, char *line, int *j, int i)
{
	char	**arr;

	arr = ft_strsplit(line, ' ');
	while (arr[i])
		i++;
	if (i == 1)
	{
		ft_li_free_arr(arr, i);
		ft_add_tube(parse, line, j);
		return ;
	}
	NAME[SIZE] = ft_strdup(arr[0]);
	COORD[SIZE][0] = ft_atoi(arr[1]);
	COORD[SIZE][1] = ft_atoi(arr[2]);
	(COORD[SIZE][0] > Y_MAX) ? Y_MAX = COORD[SIZE][0] : 0;
	(COORD[SIZE][0] < Y_MIN) ? Y_MIN = COORD[SIZE][0] : 0;
	(COORD[SIZE][1] > X_MAX) ? X_MAX = COORD[SIZE][1] : 0;
	(COORD[SIZE][1] < X_MIN) ? X_MIN = COORD[SIZE][1] : 0;
	SIZE++;
	ft_li_free_arr(arr, i);
	*j = 1;
}

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
	(COORD[SIZE][0] > Y_MAX) ? Y_MAX = COORD[SIZE][0] : 0;
	(COORD[SIZE][0] < Y_MIN) ? Y_MIN = COORD[SIZE][0] : 0;
	(COORD[SIZE][1] > X_MAX) ? X_MAX = COORD[SIZE][1] : 0;
	(COORD[SIZE][1] < X_MIN) ? X_MIN = COORD[SIZE][1] : 0;
	START = SIZE;
	SIZE = SIZE + 1;
	ft_li_free_arr(arr, i);
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
	(COORD[SIZE][0] > Y_MAX) ? Y_MAX = COORD[SIZE][0] : 0;
	(COORD[SIZE][0] < Y_MIN) ? Y_MIN = COORD[SIZE][0] : 0;
	(COORD[SIZE][1] > X_MAX) ? X_MAX = COORD[SIZE][1] : 0;
	(COORD[SIZE][1] < X_MIN) ? X_MIN = COORD[SIZE][1] : 0;
	END = SIZE;
	SIZE++;
	ft_li_free_arr(arr, i);
	*j = 1;
}

void		ft_li_comment(t_visual *parse, char *line, int *j)
{
	if (line[1] == '#')
	{
		if (!ft_strcmp(&(line[2]), "start"))
			*j = 1 << 15;
		else if (!ft_strcmp(&(line[2]), "end"))
			*j = 1 << 14;
	}
}

void	ft_go_further(t_visual *parse)
{
	int i;

	i = SIZE;
	printf("size = %d\n", SIZE);
	printf("start = %s, end = %s\nNames:\n", NAME[START], NAME[END]);
	for (i = 0; i < SIZE; i++)
		printf("%s, y = %d, x = %d\n", NAME[i], COORD[i][0], COORD[i][1]);
	for (i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
			printf("%c", MATRIX[i][j]);
		printf("\n");
	}
	printf("X_MAX = %d, X_MIN = %d\n", X_MAX, X_MIN);
	printf("Y_MAX = %d, Y_MIN = %d\n", Y_MAX, Y_MIN);
	X_RAT = (X_MAX - X_MIN) / 1200.0;
	Y_RAT = (Y_MAX - Y_MIN) / 1200.0;
	printf("%f, %f\n", X_RAT, Y_RAT);
}

int main(void)
{
	char		*line;
	t_visual	*parse;
	int			j;

	j = 0;
	for (int i = 0; i < 50; i++)
		ft_putchar('\n');
	parse = ft_init_parse();
	while (get_next_line(0, &line) > 0)
	{
		(line[0] != '#' && j >= 10 && j <= 20) ? (ft_add_tube(parse, line, &j)) : 0;
		(line[0] != '#' && j > 0 && j < 10) ? (ft_add_node(parse, line, &j, 0)) : 0;
		(j == 0) ? (j = 1) : 0;
		(j & (1 << 14)) ? (ft_li_end(parse, line, &j)) : 0;
		(j & (1 << 15)) ? (ft_li_start(parse, line, &j)) : 0;
		(line[0] == '#' && j >= 0 && j < 10) ? (ft_li_comment(parse, line, &j)) : 0;
		ft_putendl(line);
		free(line);
	}
	(j) ? (free(line)) : 0;
	ft_go_further(parse);
	return (0);
}