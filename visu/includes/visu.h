/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:39:31 by mmcclure          #+#    #+#             */
/*   Updated: 2019/03/25 16:32:52 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H
# define SCREEN_WIDTH 1200
# define SCREEN_HEIGHT 900
# define ANT_WIDTH 129
# define ANT_HEIGHT 180
# define BOX_WIDTH 188
# define BOX_HEIGHT 142

# include <SDL2_gfxPrimitives.h>
# include <SDL.h>
# include <SDL_image.h>
# include <SDL_ttf.h>
// #include "SDL_framerate.h"
// #include "SDL_gfxBlitFunc.h"
// #include "SDL_gfxPrimitives_font.h"
// #include "SDL_imageFilter.h"
// #include "SDL_rotozoom.h"  
# include "../../libft/includes/libft.h"
# include <stdlib.h>
# include <math.h>

typedef struct		s_window
{
	SDL_Window		*window;
	SDL_Renderer	*window_render;
	SDL_Texture		*background;
	SDL_Texture		*tubes;
	SDL_Texture		*ant;
	TTF_Font 		*font;
	char			quit;
}					t_window;

# define WIN_WIN	(window->window)
# define WIN_REND	(window->window_render)
# define WIN_BACK	(window->background)
# define WIN_TUBES	(window->tubes)
# define WIN_ANT	(window->ant)
# define WIN_FONT	(window->font)
# define WIN_QUIT	(window->quit)

typedef struct		s_prop
{
	float			scale;
	int				nodes_count;
	char			**matrix_adjastment;
	int				**nod_coord;
	char			**nod_names;
}					t_prop;

# define MAP_SCALE	(map->scale)
# define MAP_NODE_C	(map->nodes_count)
# define MAP_MATRIX	(map->matrix_adjastment)
# define MAP_COORDS	(map->nod_coord)
# define MAP_NAMES	(map->nod_names)

typedef struct		s_move
{
	int				dx;
	int				xy;
	int				angle;
}					t_move;


typedef struct		s_rend
{
	int				ants_start;
	int				ants_end;
	int				ants_count;
	int				frame;
	int				frame_limit;
	int				**states;
	int				cur_state;
	t_move			*moves;
}					t_rend;

# define REN_A_ST	(render->ants_start)
# define REN_A_END	(render->ants_end)
# define REN_A_CO	(render->ants_count)
# define REN_FRAME	(render->frame)
# define REN_LIMIT	(render->frame_limit)
# define REN_ST		(render->states)
# define REN_ST_CUR	(render->cur_state)
# define REN_MOVE	(render->moves)

t_window		*window_init(void);
t_prop			*prop_init(t_window *window);
t_rend			*rend_init(t_window *window, t_prop *map);

int			load_files(t_window *window, t_prop *map);
void		window_close(t_window *window);


#endif
