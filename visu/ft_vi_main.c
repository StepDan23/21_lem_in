/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vi_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:16:13 by mmcclure          #+#    #+#             */
/*   Updated: 2019/03/25 19:01:54 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/visu.h"

int node = 7;
 

void		render_back(t_window *window)
{
	SDL_Rect	clip_area;

	clip_area = (SDL_Rect){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_RenderCopy(WIN_REND, WIN_TUBES, NULL, &clip_area);
}

void		render_ant(t_window *window, int x, int y, int angle, int frame)
{
	SDL_Rect	render_area;
	SDL_Rect	clip_area;

	clip_area = (SDL_Rect){0, 0, 847, 1070};
	if (frame == 0 || frame == 2)
		clip_area.y = 2384;
	else if (frame == 1)
		clip_area.y = 1238;
	else
		clip_area.y = 126;
	render_area = (SDL_Rect){x, y, ANT_WIDTH, ANT_HEIGHT};
	SDL_RenderCopyEx(WIN_REND, WIN_ANT, &clip_area, &render_area, angle, NULL, SDL_FLIP_NONE);
}

void		render_status(t_window *window, t_rend *render)
{
	SDL_Surface	*text_surf;
	SDL_Texture	*text;
	SDL_Rect	src;
	SDL_Rect	dst;

	text_surf = TTF_RenderText_Blended(WIN_FONT, "Ants at start: 110",
									(SDL_Color){255, 255, 255, 200});
	text = SDL_CreateTextureFromSurface(WIN_REND, text_surf);
	SDL_FreeSurface(text_surf);
	src = (SDL_Rect){0, 0, 400, 100};
	dst = (SDL_Rect){460, 0, 180, 25};
	SDL_RenderCopy(WIN_REND, text, &src, &dst);
	SDL_DestroyTexture(text);
	text_surf = TTF_RenderText_Blended(WIN_FONT, "Ants at end: 110",
									(SDL_Color){255, 255, 255, 200});
	text = SDL_CreateTextureFromSurface(WIN_REND, text_surf);
	SDL_FreeSurface(text_surf);
	dst = (SDL_Rect){460 , 20, 165, 25};
	SDL_RenderCopy(WIN_REND, text, &src, &dst);
	SDL_DestroyTexture(text);
}

void		window_close(t_window *window)
{
	if (WIN_REND != NULL)
		SDL_DestroyRenderer(WIN_REND);
	if (WIN_BACK != NULL)
		SDL_DestroyTexture(WIN_BACK);
	WIN_BACK = NULL;
	if (WIN_ANT != NULL)
		SDL_DestroyTexture(WIN_ANT);
	WIN_ANT = NULL;
	if (WIN_FONT != NULL)
		TTF_CloseFont(WIN_FONT);
	WIN_FONT = NULL;
	SDL_DestroyWindow(WIN_WIN);
	WIN_WIN = NULL;
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}



int		main(void)
{
	t_window	*window;
	t_prop		*map;
	t_rend		*render;
	SDL_Event	e;

	int			x = 100;
	int			y = 100;
	int a = 1;
	int b = 1;

	if (!(window = window_init()) ||
			!(map = prop_init(window)) ||
				!(render = rend_init(window, map)) || (load_files(window, map)))
		return (0);
	while (!WIN_QUIT)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				WIN_QUIT = 1;
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_ESCAPE)
					WIN_QUIT = 1;
			}
		}
		SDL_RenderClear(WIN_REND);
		//move
		// x += 5 * a;
		// y += 5 * b;
		// if (x + 216 > SCREEN_WIDTH || x < 0)
		// 	a *= -1;
		// if (y + 300 > SCREEN_HEIGHT || y  < 0)
		// 	b *= -1;
		// move
		
		SDL_RenderSetScale(WIN_REND, 1, 1);
		SDL_RenderCopy(WIN_REND, WIN_TUBES, NULL, NULL);
		render_status(window, render);
		SDL_RenderSetScale(WIN_REND, MAP_SCALE, MAP_SCALE);
		// render_tubes(window, map);
		render_ant(window, x, y, 135, ((REN_FRAME % 32) / 8));
		SDL_RenderPresent(WIN_REND);
		REN_FRAME += (REN_FRAME == 1000) ? -1000 : 1;
		// SDL_Delay(0);
	}
	window_close(window);
	return (1);
}
