/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 15:28:56 by lshanaha          #+#    #+#             */
/*   Updated: 2019/03/26 16:09:01 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H

#include "libft.h"

typedef struct		s_visual
{
	char	**names;
	int		**coords;
	int		len;
	double	x_ratio;
	double	y_ratio;
	int		start;
	int		end;
	char	**matrix_adjastment;
	int		x_min;
	int		x_max;
	int		y_min;
	int		y_max;
	int		ant_count;
	int		**ant_moves;
	int		steps;
}					t_visual;

# define NAME (parse->names)
# define COORD (parse->coords)
# define SIZE (parse->len)
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

#endif
