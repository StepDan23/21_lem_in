/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:16:13 by mmcclure          #+#    #+#             */
/*   Updated: 2019/03/26 15:37:08 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/visu.h"

void		window_close(t_window *window)
{
	if (WIN_REND != NULL)
		SDL_DestroyRenderer(WIN_REND);
	if (WIN_BACK != NULL)
		SDL_DestroyTexture(WIN_BACK);
	if (WIN_ANT != NULL)
		SDL_DestroyTexture(WIN_ANT);
	if (FONT_NAME != NULL)
		TTF_CloseFont(FONT_NAME);
	if (FONT_STAT != NULL)
		TTF_CloseFont(FONT_STAT);
	SDL_DestroyWindow(WIN_WIN);
	WIN_BACK = NULL;
	WIN_ANT = NULL;
	FONT_STAT = NULL;
	FONT_NAME = NULL;
	WIN_WIN = NULL;
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

int			main(void)
{
	t_window	*window;
	t_prop		*map;
	t_rend		*render;
	SDL_Event	e;

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
		SDL_Delay(10);
		frame_render(window, map, render);
		
	}
	window_close(window);
	return (1);
}
