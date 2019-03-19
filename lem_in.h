/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 13:32:31 by lshanaha          #+#    #+#             */
/*   Updated: 2019/03/19 11:53:34 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <stdlib.h>

typedef struct		s_lem_in
{
	int				ant_count;
	int				start;
	int				end;
	char			***nodes;
	int				node_count;
	char			**matrix_adjacencies;
	int				flag;
}					t_lem_in;

//после построения маршрутов в структуре инпут нужен только ant_count и flags
// может стоит их добавить во вторую структуру?
typedef struct		s_routes
{
	int				**routes;
	int				*route_size;
	int				routes_count;
	int				ant_count;
}					t_routes;

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
# define ROU_ARR			(solved->routes)
# define ROU_SIZES			(solved->route_size)
# define ROU_COUN			(solved->routes_count)
# define ROU_ANT_C			(solved->ant_count)

char			ft_show_error_msg(void);
char			ft_show_error(void);
void			ft_go_further(t_lem_in *input);
void			ft_li_free_arr(char **arr, int i);
void			ft_ant_count(t_lem_in *input, char *line, int *j);
void			ft_li_comment(t_lem_in *input, char *line, int *j);
void			ft_li_start(t_lem_in *input, char *line, int *j);
void			ft_li_end(t_lem_in *input, char *line, int *j);
void			ft_init_matrix(t_lem_in *input);
void			ft_add_tube(t_lem_in *input, char *line, int *j);
void			ft_add_node(t_lem_in *input, char *line, int *j);
int				ft_place_node_in_arr(t_lem_in *input, char *str);
int				ft_num_isdigit(char *num);
t_lem_in		*ft_input_init(void);

t_routes		*lem_routes(t_lem_in *input);
#endif
