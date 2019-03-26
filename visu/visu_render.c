/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:09:44 by mmcclure          #+#    #+#             */
/*   Updated: 2019/03/26 20:13:42 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/visu.h"

static void		render_ant_pos(t_window *window, t_move pos, int frame, int fl)
{
	SDL_Rect	render_area;
	SDL_Rect	clip_area;
	int			angle;

	if (fl)
		angle = 90;
	else
		angle = pos.angle - 270;
	clip_area = (SDL_Rect){0, 0, 847, 1070};
	if (frame == 0 || frame == 2)
		clip_area.y = 2384;
	else if (frame == 1)
		clip_area.y = 1238;
	else
		clip_area.y = 126;
	render_area = (SDL_Rect){pos.x - ANT_WIDTH / 2,
					pos.y - ANT_HEIGHT / 2, ANT_WIDTH, ANT_HEIGHT};
	SDL_RenderCopyEx(WIN_REND, WIN_ANT, &clip_area,
						&render_area, angle, NULL, SDL_FLIP_NONE);
}

static void		calc_move(t_prop *map, t_rend *render)
{
	int		ant_num;
	int		d_x;
	int		d_y;

	ant_num = ANTS_COU - 1;
	while (ant_num >= 0)
	{
		if (STATES[ST_CUR][ant_num] == -1)
			T_MOVE[ant_num] = (t_move){T_MOVE[ant_num].x,
								T_MOVE[ant_num].y, 0, 0, 0};
		else if (STATES[ST_CUR][ant_num] != -1)
		{
			d_x = MAP_COORDS[STATES[ST_CUR][ant_num]][0] - T_MOVE[ant_num].x;
			d_y = MAP_COORDS[STATES[ST_CUR][ant_num]][1] - T_MOVE[ant_num].y;
			T_MOVE[ant_num].dx = d_x / (float)FR_LIMIT * 1.2;
			T_MOVE[ant_num].dy = d_y / (float)FR_LIMIT * 1.2;
			T_MOVE[ant_num].angle = atan2((float)d_y, (float)d_x) * 180 / M_PI;
		}
		ant_num--;
	}
	ST_CUR++;
}

static void		render_start_end(t_window *window, t_prop *map, t_rend *render)
{
	int		ant_num;

	ant_num = -1;
	if (FR_CUR == 0.2 * FR_LIMIT + 1)
	{
		ANTS_START = 0;
		while (++ant_num < ANTS_COU)
			if (T_MOVE[ant_num].x == MAP_COORDS[POS_START][0]
					&& T_MOVE[ant_num].y == MAP_COORDS[POS_START][1])
				ANTS_START++;
	}
	if (FR_CUR == FR_LIMIT)
	{
		ANTS_END = 0;
		while (++ant_num < ANTS_COU)
			if (T_MOVE[ant_num].x / MAP_COORDS[POS_END][0] > 0.92
					&& T_MOVE[ant_num].y / MAP_COORDS[POS_END][1] > 0.92)
				ANTS_END++;
	}
	if (ANTS_START != 0)
		render_ant_pos(window, (t_move){MAP_COORDS[POS_START][0],
								MAP_COORDS[POS_START][1], 0, 0, 0}, 0, 0);
	if (ANTS_END != 0)
		render_ant_pos(window, (t_move){MAP_COORDS[POS_END][0],
									MAP_COORDS[POS_END][1], 0, 0, 0}, 0, 0);
}

static void		render_ants(t_window *window, t_prop *map, t_rend *render)
{
	int		ant_num;

	ant_num = -1;
	if (ST_CUR <= ST_LAST)
	{
		if (FR_CUR == 0)
			calc_move(map, render);
		else if (FR_CUR < 0.2 * FR_LIMIT)
		{
			while (++ant_num < ANTS_COU)
				if (T_MOVE[ant_num].dx != 0 || T_MOVE[ant_num].dy != 0)
					render_ant_pos(window, T_MOVE[ant_num], 0, 1);
		}
		else
			while (++ant_num < ANTS_COU)
				if (T_MOVE[ant_num].dx != 0 || T_MOVE[ant_num].dy != 0)
				{
					T_MOVE[ant_num].x += T_MOVE[ant_num].dx;
					T_MOVE[ant_num].y += T_MOVE[ant_num].dy;
					render_ant_pos(window, T_MOVE[ant_num], FR_CUR % 32 / 8, 0);
				}
	}
	render_start_end(window, map, render);
}

void			frame_render(t_window *window, t_prop *map, t_rend *render)
{
	SDL_RenderClear(WIN_REND);
	SDL_RenderSetScale(WIN_REND, 1, 1);
	SDL_RenderCopy(WIN_REND, WIN_BACK, NULL, NULL);
	print_status(window, render, 1);
	SDL_RenderSetScale(WIN_REND, MAP_SCALE, MAP_SCALE);
	render_ants(window, map, render);
	SDL_RenderPresent(WIN_REND);
	FR_CUR += (FR_CUR == FR_LIMIT) ? -FR_LIMIT : 1;
}
