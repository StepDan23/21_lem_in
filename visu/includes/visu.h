/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:39:31 by mmcclure          #+#    #+#             */
/*   Updated: 2019/03/26 16:45:48 by mmcclure         ###   ########.fr       */
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
# define F_STAT 25

# include <SDL2_gfxPrimitives.h>
# include <SDL.h>
# include <SDL_image.h>
# include <SDL_ttf.h>
# include "../../libft/includes/libft.h"
# include <stdlib.h>
# include <math.h>

typedef struct		s_window
{
	SDL_Window		*window;
	SDL_Renderer	*window_render;
	SDL_Texture		*background;
	SDL_Texture		*ant;
	TTF_Font		*f_names;
	TTF_Font		*f_status;
	char			quit;
}					t_window;

# define WIN_WIN	(window->window)
# define WIN_REND	(window->window_render)
# define WIN_BACK	(window->background)
# define WIN_ANT	(window->ant)
# define FONT_NAME	(window->f_names)
# define FONT_STAT	(window->f_status)
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
	float			x;
	float			y;
	float			dx;
	float			dy;
	int				angle;
}					t_move;

typedef struct		s_rend
{
	int				ants_start;
	int				ants_end; 
	int				ants_count;// yours
	int				frame_current;
	int				frame_limit;
	int				**states; //new matrix
	int				current_state;
	int				last_state;
	int				pos_start;   // start end
	int				pos_end;   // start end
	t_move			*moves;
}					t_rend;

# define ANTS_START	(render->ants_start)
# define ANTS_END	(render->ants_end)
# define ANTS_COU	(render->ants_count)
# define FR_CUR		(render->frame_current)
# define FR_LIMIT	(render->frame_limit)
# define STATES		(render->states)
# define ST_CUR		(render->current_state)
# define ST_LAST	(render->last_state)
# define POS_START	(render->pos_start)
# define POS_END	(render->pos_end)
# define T_MOVE		(render->moves)

t_window			*window_init(void);
t_prop				*prop_init(t_window *window);
t_rend				*rend_init(t_window *window, t_prop *map);

int					load_files(t_window *window, t_prop *map);
void				window_close(t_window *window);
void				frame_render(t_window *window, t_prop *map, t_rend *render);

#endif
