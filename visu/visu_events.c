/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 13:11:16 by mmcclure          #+#    #+#             */
/*   Updated: 2019/03/28 13:34:00 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/visu.h"

static void		event_to_start(t_prop *map, t_rend *render)
{
	int		i;

	i = 0;
	ANTS_START = ANTS_COU;
	FR_CUR = 0;
	ST_CUR = 0;
	ANTS_END = 0;
	while (i < ANTS_COU)
	{
		T_MOVE[i].x = MAP_COORDS[POS_START][0];
		T_MOVE[i].y = MAP_COORDS[POS_START][1];
		i++;
	}
}

static void		event_speed(t_rend *render, int up)
{
	if (up)
	{
		FR_LIMIT *= 0.8;
		FR_LIMIT = (FR_LIMIT < 10) ? 10 : FR_LIMIT;
		FR_CUR = 0;
		ST_CUR -= 1;
	}
	else
	{
		FR_LIMIT *= 1.2;
		FR_LIMIT = (FR_LIMIT > 400) ? 400 : FR_LIMIT;
		FR_CUR = 0;
		ST_CUR -= 1;
	}
}

void			win_events(t_window *window, t_prop *map, t_rend *render)
{
	SDL_Event	e;

	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
			WIN_QUIT = 1;
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_ESCAPE)
				WIN_QUIT = 1;
			else if (e.key.keysym.sym == SDLK_SPACE)
				event_to_start(map, render);
			else if (e.key.keysym.sym == SDLK_UP)
				event_speed(render, 1);
			else if (e.key.keysym.sym == SDLK_DOWN)
				event_speed(render, 0);
		}
	}
}
