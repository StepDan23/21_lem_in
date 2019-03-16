/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_li_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 13:31:55 by lshanaha          #+#    #+#             */
/*   Updated: 2019/03/16 15:25:51 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"]
#include <stdlib.h>

char		ft_show_error_msg(void)
{
	ft_putstrt("Some error oqqured\n");
	return (1);
}

char		ft_show_error(void)
{
	ft_putstrt("ERROR\n");
	return (1);
}

int			ft_num_isdigit(char *num)
{
	int	i;

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
	return (0);
}

t_lem_in	*ft_input_init(void)
{
	t_lem_in	*input;

	input = malloc(sizeof(t_lem_in));
	INP_NODES = malloc(8 * 3 * 10000);
	INP_NODES_NAMES = malloc(8 * 10000);
	INP_NODES_XS = malloc(8 * 10000);
	INP_NODES_YS = malloc(8 * 10000);
	INP_ANT_C = 0;
	INP_START = 0;
	INP_END = 0;
	INP_NODE_C = 0;
	return (0);
}


//подсчитываем количество муравьишек, Проверяем - число ли это
// и не превышает ли оно int.
void		ft_ant_count(t_lem_in *input, char *line, int *j)
{
	int		res;

	if (ft_num_isdigit(line))
		exit(ft_show_error());
	res = ft_atoi(line);
	if (ft_atol(line) != res)
		exit(ft_show_error());
	INP_ANT_C = res;
	*j = 1;
}

void		ft_li_comment(t_lem_in *input, char *line, int *j)
{
	if (line[1] == '#')
	{
		if (!ft_strcmp(&(line[2]), "start"))
			*j = 1 << 15;
		else if (!ft_strcmp(&(line[2]), "end"))
			*j = 1 << 14;
		else
			exit(ft_show_error());
	}
}


void		ft_li_start(t_lem_in *input, char *line, int *j)
{
	char	**arr;
	int		i;

	arr  = ft_strsplit(line, ' ');
	i = 0;
	while (arr[i])
		i++;
	if (i != 3)
		exit(ft_show_error());
	if (ft_num_isdigit(arr[1]) || ft_num_isdigit(arr[1]))
		exit(ft_show_error());
	INP_NODES_NAMES = ft_strdup(arr[0]);
	INP_NODES_XS = ft_strdup(arr[1]);
	INP_NODES_XS = ft_strdup(arr[2]);
	free(arr[2]);
	free(arr[1]);
	free(arr[0]);
	INP_START = INP_NODES_NAMES;
	free(arr);
}

void		ft_li_end(t_lem_in *input, char *line, int *j)
{

}

int			main(void)
{
	char		*line;
	char		**arr;
	t_lem_in	*input;
	int			j;
	int			i;

	j = 0;
	input = ft_input_init();
	while (get_next_line(0, line) > 0)
	{
		(j == 0) ? (ft_ant_count(input, line, &j)) : 0;
		(j & (1 << 14)) ? (ft_li_end(input, line, &j)) : 0;
		(j & (1 << 15)) ? (ft_li_start(input, line, &j)) : 0;
		(line[0] == '#') ? (ft_li_comment(input, line, &j)) : 0;
		free(line);
	}
	(j) ? (free(line)) : 0;
	return (1);
}
