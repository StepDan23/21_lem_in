/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 13:32:31 by lshanaha          #+#    #+#             */
/*   Updated: 2019/03/27 15:37:30 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../../libft/includes/libft.h"
# include <stdlib.h>

typedef struct		s_lem_in
{
	int				ant_count;
	int				start;
	int				end;
	char			***nodes;
	int				node_count;
	char			**matrix_adjacencies;
	char			**stones;
	int				stones_count;
}					t_lem_in;

typedef struct		s_routes
{
	char			***routes;
	int				*route_size;
	int				routes_count;
	int				ant_count;
	int				*num_of_ants;
	int				num_of_ways;
	int				*num_finished;
	int				*num_left;
	int				*ant_offset;
}					t_routes;

/*
** ROU_ARR			- маршруты
** ROU_SIZES		- размеры каждого пути рассчитаных алгоритмом
** ROU_COUN			- количество путей рассчитанных алгоритмом
** ROU_ANT_C		- количество муравьев всего
** ROU_ANT_NUM		- Количество муравьев на каждом из путей
** ROU_NUM_WAYS		- количество активных путей (путей в которых кол-во
** муравьев больше 0)
** ROU_ANT_FIN		- количество муравьев в конечной точке на кажом из путей
** ROU_ANT_LEFT		- массив с количеством муравьев ожидающих выхода на каждом
**					  из путей
** ROU_ANT_OFFSET	- позиция первого муравья в маршруте (когда первый муравей
**					  доходит до конца значение не меняется)
*/

# define INP_ANT_C			(input->ant_count)
# define INP_START			(input->start)
# define INP_END			(input->end)
# define INP_NODES			(input->nodes)
# define INP_NODES_NAMES	(input->nodes)[0]
# define INP_NODES_XS		(input->nodes)[1]
# define INP_NODES_YS		(input->nodes)[2]
# define INP_NODE_C			(input->node_count)
# define INP_MATRIX			(input->matrix_adjacencies)
# define INP_FLAG			(input->flag)
# define INP_STONES			(input->stones)
# define INP_STONES_C		(input->stones_count)

# define ROU_ARR			(solved->routes)
# define ROU_SIZES			(solved->route_size)
# define ROU_COUN			(solved->routes_count)
# define ROU_ANT_C			(solved->ant_count)
# define ROU_ANT_NUM		(solved->num_of_ants)
# define ROU_NUM_WAYS		(solved->num_of_ways)
# define ROU_ANT_FIN		(solved->num_finished)
# define ROU_ANT_LEFT		(solved->num_left)
# define ROU_ANT_OFFSET		(solved->ant_offset)

char				ft_show_error_msg(void);
char				ft_show_error(void);
void				ft_go_further(t_lem_in *input);
void				ft_li_free_arr(char **arr, int i);
void				ft_ant_count(t_lem_in *input, char *line, int *j);
void				ft_li_comment(t_lem_in *input, char *line, int *j);
void				ft_li_start(t_lem_in *input, char *line, int *j);
void				ft_li_end(t_lem_in *input, char *line, int *j);
void				ft_init_matrix(t_lem_in *input);
void				ft_tube(t_lem_in *input, char *line, int *j);
void				ft_node(t_lem_in *input, char *line, int *j, int i);
int					ft_place_node_in_arr(t_lem_in *input, char *str);
int					ft_num_isdigit(char *num);
t_lem_in			*ft_input_init(void);
void				ft_lemmin_moves(t_routes *solved, int k, int n);

/*
** ft_li_routes_helpers.c
*/
t_routes			*rou_init(t_lem_in *input);
int					lem_intcmp(int *line, int j, int size);
int					*lem_intnew(int size);
void				lem_free_tlem(t_lem_in *input);
/*
** ft_li_routes.c
*/
t_routes			*lem_routes(t_lem_in *input);
void				ft_route_all_ants(t_routes *solved, int i);

#endif
