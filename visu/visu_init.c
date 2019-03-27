/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 19:01:47 by mmcclure          #+#    #+#             */
/*   Updated: 2019/03/27 15:43:54 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/visu.h"

t_window		*window_init(void)
{
	t_window	*window;

	window = (t_window*)malloc(sizeof(t_window));
	WIN_QUIT = 0;
	if (SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() < 0)
	{
		ft_printf("Init_Error: %s\n", SDL_GetError());
		return (NULL);
	}
	WIN_WIN = SDL_CreateWindow("Vizualizer", SDL_WINDOWPOS_UNDEFINED,\
	SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (WIN_WIN == NULL)
	{
		ft_printf("Init_Window_Error: %s\n", SDL_GetError());
		return (NULL);
	}
	WIN_REND = SDL_CreateRenderer(WIN_WIN, -1, SDL_RENDERER_ACCELERATED);
	if (WIN_REND == NULL)
	{
		ft_printf("Init_Renderer_Error: %s\n", SDL_GetError());
		return (NULL);
	}
	return (window);
}

t_prop			*prop_init(t_window *window, t_visual *parse)
{
	t_prop		*map;
	int			i;

	if (!(map = (t_prop*)malloc(sizeof(t_prop))))
		return (0);
	SCALE_ANT = 0.5;
	MAP_NODE_C = SIZE;
	MAP_MATRIX = MATRIX;
	MAP_COORDS = COORD;
	i = -1;
	while (++i < MAP_NODE_C)
	{
		MAP_COORDS[i][0] = MAP_COORDS[i][0] * X_RAT - X_MIN * 0.4 * X_RAT;
		MAP_COORDS[i][1] = MAP_COORDS[i][1] * Y_RAT - Y_MIN * 0.4 * Y_RAT;
	}
	MAP_NAMES = NAME;
	ft_printf("EXIT FROM PROP\n");
	return (map);
}

t_rend			*rend_init(t_prop *map, t_visual *parse)
{
	t_rend	*render;
	int		i;

	i = 0;
	if (!(render = (t_rend*)malloc(sizeof(t_rend))))
		return (0);
	FR_CUR = 0;
	FR_LIMIT = 100;
	ANTS_END = 0;
	ANTS_START = ANT_C;
	ANTS_COU = ANT_C;
	STATES = ANT_MOVE;
	ST_LAST = STEPS;
	ST_CUR = 0;
	POS_START = START;
	POS_END = END;
	T_MOVE = (t_move*)ft_memalloc(sizeof(t_move) * ANTS_COU);
	while (i < ANTS_COU)
	{
		T_MOVE[i].x = MAP_COORDS[POS_START][0];
		T_MOVE[i].y = MAP_COORDS[POS_START][1];
		i++;
	}
	ft_printf("START = %d END = %d\n", START, END);
	ft_printf("EXIT FROM REND\n");

	return (render);
}
