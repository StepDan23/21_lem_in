/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:39:31 by mmcclure          #+#    #+#             */
/*   Updated: 2019/03/23 13:22:21 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H
# define SCREEN_WIDTH 1200
# define SCREEN_HEIGHT 900

# include "SDL.h"
# include "SDL_image.h"
# include "../../libft/includes/libft.h"
# include <stdlib.h>

typedef struct		s_visu
{
	SDL_Window		*window;
	SDL_Renderer	*window_render;
	SDL_Texture		*background;
	SDL_Texture		*foo;
	char			quit;
}					t_visu;

typedef struct		s_ants
{
	int				ants_start;
	int				ants_end;
	int				ants_sum;
	SDL_Window		*window;
	SDL_Renderer	*window_render;
	SDL_Texture		*background;
	SDL_Texture		*foo;
	char			quit;
}					t_ants;

# define WIN_WIN	(window->window)
# define WIN_REND	(window->window_render)
# define WIN_BACK	(window->background)
# define WIN_QUIT	(window->quit)
# define WIN_ANT	(window->foo)
#endif
