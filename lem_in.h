/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 13:32:31 by lshanaha          #+#    #+#             */
/*   Updated: 2019/03/18 12:53:38 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <stdlib.h>

typedef struct	s_lem_in
{
	int		ant_count;
	int		start;
	int		end;
	char	***nodes;
	int		node_count;
	char	**matrix_adjacencies;
	int		flag;
}				t_lem_in;

typedef struct	s_routes
{
	int		**routes;
	int		*route_size;
	int		routes_count;
}				t_routes;

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

#endif
