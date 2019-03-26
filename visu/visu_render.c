/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:09:44 by mmcclure          #+#    #+#             */
/*   Updated: 2019/03/26 16:57:49 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/visu.h"

static void		render_status(t_window *window, t_rend *render)
{
	SDL_Surface	*text_surf;
	SDL_Texture	*text;
	SDL_Rect	src;
	SDL_Rect	dst;

	text_surf = TTF_RenderText_Blended(FONT_STAT, "Ants at start: 110",
									(SDL_Color){255, 255, 255, 200});
	text = SDL_CreateTextureFromSurface(WIN_REND, text_surf);
	SDL_FreeSurface(text_surf);
	src = (SDL_Rect){0, 0, 200, F_STAT};
	dst = (SDL_Rect){460, 0, 200, F_STAT};
	SDL_RenderCopy(WIN_REND, text, &src, &dst);
	SDL_DestroyTexture(text);
	text_surf = TTF_RenderText_Blended(FONT_STAT, "Ants at end: 110",
									(SDL_Color){255, 255, 255, 200});
	text = SDL_CreateTextureFromSurface(WIN_REND, text_surf);
	SDL_FreeSurface(text_surf);
	dst = (SDL_Rect){460, F_STAT, 180, F_STAT};
	SDL_RenderCopy(WIN_REND, text, &src, &dst);
	SDL_DestroyTexture(text);
}

static void		render_ant_pos(t_window *window, t_move pos, int frame, int flag)
{
	SDL_Rect	render_area;
	SDL_Rect	clip_area;
	int			angle;

	if (flag)
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
	render_area = (SDL_Rect){pos.x - ANT_WIDTH / 2, pos.y - ANT_HEIGHT/ 2, ANT_WIDTH, ANT_HEIGHT};
	SDL_RenderCopyEx(WIN_REND, WIN_ANT, &clip_area,
						&render_area, angle, NULL, SDL_FLIP_NONE);
}

void			calc_move(t_prop *map, t_rend *render)
{
	int		ant_num;
	int		d_x;
	int		d_y;

	ant_num = ANTS_COU - 1;
	while (ant_num >= 0)
	{
		ft_printf("%d st-%d states-%d\n", ant_num, ST_CUR, STATES[ST_CUR][ant_num]);
		if ((ST_CUR > ST_LAST) || STATES[ST_CUR][ant_num] == -1)
			T_MOVE[ant_num] = (t_move){T_MOVE[ant_num].x, T_MOVE[ant_num].y, 0, 0, 0};
		else if (STATES[ST_CUR][ant_num] != -1)
		{
			d_x = MAP_COORDS[STATES[ST_CUR][ant_num]][0] - T_MOVE[ant_num].x;
			d_y = MAP_COORDS[STATES[ST_CUR][ant_num]][1] - T_MOVE[ant_num].y;
			T_MOVE[ant_num].dx = d_x / (float) FR_LIMIT * 1.1;
			T_MOVE[ant_num].dy = d_y / (float) FR_LIMIT * 1.1;
			T_MOVE[ant_num].angle = atan2((float)d_y,(float)d_x) * 180 / M_PI;
				ft_printf("dx-%f dy-%f angle-%d\n", T_MOVE[ant_num].dx,T_MOVE[ant_num].dy, T_MOVE[ant_num].angle);
		}
		ant_num--;
	}
	ST_CUR++;
}

static void		render_ants(t_window *window, t_prop *map, t_rend *render)
{
	int		ant_num;

	ant_num = -1;
	if (FR_CUR == 0)
		calc_move(map, render);
	else if (FR_CUR < 0.1 * FR_LIMIT)
	{
		while (++ant_num < ANTS_COU)
			if (T_MOVE[ant_num].dx != 0 || T_MOVE[ant_num].dy != 0)
				render_ant_pos(window, T_MOVE[ant_num], 0, 1);
				
	}
	else
		{
			while (++ant_num < ANTS_COU)
			if (T_MOVE[ant_num].dx != 0 || T_MOVE[ant_num].dy != 0)
			{
				T_MOVE[ant_num].x += T_MOVE[ant_num].dx;
				T_MOVE[ant_num].y += T_MOVE[ant_num].dy;
				render_ant_pos(window, T_MOVE[ant_num], FR_CUR % 32 / 8, 0);
			}
				ft_printf("frame--%d\n", FR_CUR);
		}
	if (ANTS_START != 0)
		render_ant_pos(window, 
			(t_move){MAP_COORDS[POS_START][0], MAP_COORDS[POS_START][1], 0, 0, 0}, 0, 1);
	if (ANTS_END != 0)
		render_ant_pos(window, 
			(t_move){MAP_COORDS[POS_END][0], MAP_COORDS[POS_END][1], 0, 0, 0}, 0, 1);

}

void		frame_render(t_window *window, t_prop *map, t_rend *render)
{
		SDL_RenderClear(WIN_REND);
		//move
		// x += 5 * a;
		// y += 5 * b;
		// if (x + 216 > SCREEN_WIDTH || x < 0)
		// 	a *= -1;
		// if (y + 300 > SCREEN_HEIGHT || y  < 0)
		// 	b *= -1;
		// move and angle
		SDL_RenderSetScale(WIN_REND, 1, 1);
		SDL_RenderCopy(WIN_REND, WIN_BACK, NULL, NULL);
		render_status(window, render);
		SDL_RenderSetScale(WIN_REND, MAP_SCALE, MAP_SCALE);
		render_ants(window, map, render);
		SDL_RenderPresent(WIN_REND);
		FR_CUR += (FR_CUR == FR_LIMIT) ? -FR_LIMIT : 1;
}

