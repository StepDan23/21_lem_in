/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_li_input_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 21:13:34 by lshanaha          #+#    #+#             */
/*   Updated: 2019/03/20 18:56:36 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

char		ft_show_error_msg(void)
{
	ft_putstr_fd("Some error oqqured\n", 2);
	return (1);
}

char		ft_show_error(void)
{
	ft_putstr_fd("ERROR\n", 2);
	return (1);
}

void		ft_li_free_arr(char **arr, int i)
{
	int		j;

	j = 0;
	while (j < i)
	{
		free(arr[j]);
		j++;
	}
	free(arr);
}

t_lem_in	*ft_input_init(void)
{
	t_lem_in	*input;

	input = malloc(sizeof(t_lem_in));
	INP_NODES = malloc(8 * 3);
	if (!input || !INP_NODES)
		exit(ft_show_error_msg());
	INP_NODES_NAMES = malloc(8 * 10000);
	INP_NODES_XS = malloc(8 * 10000);
	INP_NODES_YS = malloc(8 * 10000);
	if (!INP_NODES_NAMES || !INP_NODES_XS || !INP_NODES_YS)
		exit(ft_show_error_msg());
	INP_ANT_C = -1;
	INP_START = -1;
	INP_END = -1;
	INP_NODE_C = 0;
	INP_MATRIX = NULL;
	return (input);
}

int			ft_num_isdigit(char *num)
{
	int			i;
	long long	temp;

	i = 0;
	while (num[i] == ' ' || num[i] == '\t')
		i++;
	if (num[i] == '-' || num[i] == '+')
		i++;
	while (num[i])
	{
		if (num[i] < '0' || num[i] > '9')
			return (1);
		i++;
	}
	temp = ft_atol(num);
	if (temp < -2147483648 || temp > 2147483647)
		return (1);
	return (0);
}
