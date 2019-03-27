/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 14:23:22 by lshanaha          #+#    #+#             */
/*   Updated: 2019/03/27 16:06:22 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./includes/visu.h"

void		ft_visual_tests(t_visual *parse)
{

	ft_printf("=========================in tests=======================\n");

	ft_printf("SIZE = %d\nNAMES:\n", SIZE);
	for (int i = 0; i < SIZE; i++)
		ft_printf("%s ", NAME[i]);
	ft_printf("\nCOORDS X|Y:\n");
	for (int i = 0; i < SIZE; i++)
		ft_printf("%d|%d ", COORD[i][0], COORD[i][1]);
	ft_printf("\nX_RAT/Y_RAT:\n%f/%f\n", X_RAT, Y_RAT);
	for (int i = 0; i < SIZE; i++)
		ft_printf("%s\n", MATRIX[i]);
	ft_printf("START = %d, END = %d \n", START, END);
	ft_printf("ANT_COUNT = %d\n", ANT_C);
	for (int i = 0; i < STEPS; i++)
	{
		for (int j = 0; j < ANT_C; j++)
			ft_printf("%3d ", ANT_MOVE[i][j]);
		ft_putchar('\n');
	}
	ft_printf("X_MAX = %d, Y_MAX = %d\n", X_MAX, Y_MAX);
	ft_printf("X_MIN = %d, Y_MIN = %d\n", X_MIN, Y_MIN);
	ft_printf("=========================out tests=======================\n");
}

void		ft_shortest_distance(t_visual *parse, int i, int j, double dist)
{
	while (i < SIZE)
	{
		j = i + 1;
		while (j < SIZE)
		{
			dist = (double)((COORD[i][1] - COORD[j][1]) ^ 2 +\
			(COORD[i][0] - COORD[j][0]) ^ 2);
			if (dist < SH_DIST)
			{
				SH_DIST = dist;
				SH_DIST_FIRST = i;
				SH_DIST_SECOND = j;
			}
			if (dist > BIG_DIST)
			{
				BIG_DIST = dist;
				BIG_DIST_FIRST = i;
				BIG_DIST_SECOND = j;
			}
			j++;
		}
		i++;
	}
	SH_DIST = sqrt(SH_DIST);
	BIG_DIST = sqrt(BIG_DIST);
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

void		ft_ant_count(t_visual *parse, char *line, int *j)
{
	int		res;

	res = ft_atoi(line);
	ANT_C = res;
	*j = 1;
}


void		ft_ant_move_parse(t_visual *parse, char *line, int *j)
{
	int		i;
	int		k;
	char	**all_ants;
	char	**ant_data;

	(ANT_MOVE == 0) ? ft_init_steps(parse) : 0;
	all_ants = ft_strsplit(line, ' ');
	i = 0;
	while (all_ants[i])
	{
		ant_data = ft_strsplit(&(all_ants[i][1]), '-');
		k = ft_place_node_in_arr(parse, ant_data[1]);
		ANT_MOVE[STEPS][ft_atoi(ant_data[0]) - 1] = k;
		ft_li_free_char_arr(ant_data, 2);
		i++;
	}
	ft_li_free_char_arr(all_ants, i - 1);
	STEPS++;
}

t_visual		*ft_parse_income_from_lem_in(void)
{
	char		*line;
	t_visual	*parse;
	int			j;

	j = 0;
	parse = ft_init_parse();
	while (get_next_line(0, &line) > 0)
	{
		(line[0] != '#' && j >= 10 && j <= 20) ? (ft_add_tube(parse, line, &j)) : 0;
		(line[0] != '#' && j > 0 && j < 10) ? (ft_add_node(parse, line, &j, 0)) : 0;
		(j == 0) ? ft_ant_count(parse, line, &j) : 0;
		(j & (1 << 14)) ? (ft_li_end(parse, line, &j)) : 0;
		(j & (1 << 15)) ? (ft_li_start(parse, line, &j)) : 0;
		(line[0] == '#' && j >= 0 && j < 10) ? (ft_li_comment(parse, line, &j)) : 0;
		(line[0] == 'L') ? ft_ant_move_parse(parse, line, &j) : 0;
		free(line);
	}
	(j) ? (free(line)) : 0;
	X_RAT = 1100.0 / X_MAX;
	Y_RAT = 850.0 / Y_MAX;
	ft_shortest_distance(parse, 0, 0, 0.0);
	ft_visual_tests(parse);

	return (parse);
}
