/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:39:31 by mmcclure          #+#    #+#             */
/*   Updated: 2019/03/27 23:16:41 by lshanaha         ###   ########.fr       */
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
	float			scale_ant;
}					t_window;

# define WIN_WIN	(window->window)
# define WIN_REND	(window->window_render)
# define WIN_BACK	(window->background)
# define WIN_ANT	(window->ant)
# define FONT_NAME	(window->f_names)
# define FONT_STAT	(window->f_status)
# define WIN_QUIT	(window->quit)
# define SCALE_ANT	(window->scale_ant)

typedef struct		s_move
{
	float			x;
	float			y;
	float			dx;
	float			dy;
	int				angle;
}					t_move;

typedef struct		s_prop
{
	int				nodes_count;
	char			**matrix_adjastment;
	int				**nod_coord;
	char			**nod_names;
}					t_prop;

# define MAP_NODE_C	(map->nodes_count)
# define MAP_MATRIX	(map->matrix_adjastment)
# define MAP_COORDS	(map->nod_coord)
# define MAP_NAMES	(map->nod_names)

typedef struct		s_rend
{
	int				ants_start;
	int				ants_end;
	int				ants_count;
	int				frame_current;
	int				frame_limit;
	int				**states;
	int				current_state;
	int				last_state;
	int				pos_start;
	int				pos_end;
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
# define STATES_LEN (render->states_len)

typedef struct		s_visual
{
	char			**names;
	int				**coords;
	int				node_count;
	double			x_ratio;
	double			y_ratio;
	int				start;
	int				end;
	char			**matrix_adjastment;
	int				x_min;
	int				x_max;
	int				y_min;
	int				y_max;
	int				ant_count;
	int				**ant_moves;
	int				steps;
	double			shortest_dist;
	int				shortest_first;
	int				shortest_second;
	double			biggest_dist;
	int				biggest_first;
	int				biggest_second;
}					t_visual;

# define NAME (parse->names)
# define COORD (parse->coords)
# define SIZE (parse->node_count)
# define X_RAT (parse->x_ratio)
# define Y_RAT (parse->y_ratio)
# define MATRIX (parse->matrix_adjastment)
# define START (parse->start)
# define END (parse->end)
# define X_MIN (parse->x_min)
# define X_MAX (parse->x_max)
# define Y_MIN (parse->y_min)
# define Y_MAX (parse->y_max)
# define ANT_C (parse->ant_count)
# define ANT_MOVE (parse->ant_moves)
# define STEPS (parse->steps)
# define SH_DIST (parse->shortest_dist)
# define SH_DIST_FIRST (parse->shortest_first)
# define SH_DIST_SECOND (parse->shortest_second)
# define BIG_DIST (parse->biggest_dist)
# define BIG_DIST_FIRST (parse->biggest_first)
# define BIG_DIST_SECOND (parse->biggest_second)

t_visual			*ft_init_parse(int i);
void				ft_init_matrix(t_visual *parse);
void				ft_init_steps(t_visual *parse);
void				ft_li_free_char_arr(char **arr, int i);
int					ft_show_error(void);
void				ft_li_comment(t_visual *parse, char *line, int *j);
void				ft_tube(t_visual *parse, char *line, int *j);
void				ft_node(t_visual *parse, char *line, int *j, int i);
void				ft_li_end(t_visual *parse, char *line, int *j);
void				ft_li_start(t_visual *parse, char *line, int *j);
int					ft_place_node_in_arr(t_visual *parse, char *str);
void				ft_go_further(t_visual *parse);
void				ft_ant_count(t_visual *parse, char *line, int *j, int f);
void				ft_ant_move_parse(t_visual *parse, char *line, int *j);
t_visual			*ft_parse_income_from_lem_in(void);

t_window			*window_init(void);
t_prop				*prop_init(t_window *window, t_visual *parse);
t_rend				*rend_init(t_prop *map, t_visual *parse);

int					load_files(t_window *window, t_prop *map);

void				frame_render(t_window *window, t_prop *map, t_rend *render);

void				print_status(t_window *window, t_rend *render, int len);
void				print_inst(t_window *window, t_rend *render);

void				win_events(t_window *window, t_prop *map, t_rend *render);

void				ft_visual_tests(t_visual *parse);
#endif
