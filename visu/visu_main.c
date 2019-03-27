/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:16:13 by mmcclure          #+#    #+#             */
/*   Updated: 2019/03/27 23:14:30 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/visu.h"

static void		window_close(t_window *window)
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

int				main(void)
{
	t_window	*window;
	t_prop		*map;
	t_rend		*render;
	t_visual	*parse;

	parse = ft_parse_income_from_lem_in();
	if (!(window = window_init()) ||
			!(map = prop_init(window, parse)) ||
				!(render = rend_init(map, parse)) ||
											(load_files(window, map)))
		return (0);
	while (!WIN_QUIT)
	{
		win_events(window, map, render);
		SDL_Delay(10);
		frame_render(window, map, render);
	}
	window_close(window);
	return (1);
}
