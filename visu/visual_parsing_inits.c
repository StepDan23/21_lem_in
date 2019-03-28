/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_parsing_inits.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 17:44:29 by lshanaha          #+#    #+#             */
/*   Updated: 2019/03/28 13:21:42 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/visu.h"
#include <stdlib.h>

t_visual	*ft_init_parse(int i)
{
	t_visual	*parse;

	parse = malloc(sizeof(t_visual));
	(!parse) ? exit(ft_show_error()) : 0;
	NAME = malloc(8 * 10000);
	COORD = malloc(8 * 10000);
	while (++i < 10000)
	{
		COORD[i] = (int *)malloc(8);
		(!(COORD[i])) ? exit(ft_show_error()) : 0;
	}
	SIZE = 0;
	X_RAT = 1;
	Y_RAT = 1;
	MATRIX = NULL;
	ANT_MOVE = NULL;
	X_MAX = -1;
	Y_MAX = -1;
	X_MIN = 2000000000;
	Y_MIN = 2000000000;
	STEPS = 0;
	SH_DIST = 100000000.0;
	BIG_DIST = 0.0;
	return (parse);
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
			ft_li_free_char_arr(arr, j);
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

void		ft_init_steps(t_visual *parse)
{
	int		i;
	int		k;

	i = 0;
	ANT_MOVE = malloc(8 * 10000);
	(!ANT_MOVE) ? exit(ft_show_error()) : 0;
	while (i < ANT_C + SIZE)
	{
		ANT_MOVE[i] = ft_memalloc(4 * ANT_C);
		(!(ANT_MOVE[i])) ? exit(ft_show_error()) : 0;
		k = 0;
		while (k < ANT_C)
			ANT_MOVE[i][k++] = -1;
		i++;
	}
	ANT_MOVE[i] = NULL;
}

int			ft_show_error(void)
{
	ft_putstr_fd("ERROR\n", 2);
	return (1);
}

void		ft_li_free_char_arr(char **arr, int i)
{
	int		j;

	j = 0;
	while (j < i)
		free(arr[j++]);
	free(arr);
}
