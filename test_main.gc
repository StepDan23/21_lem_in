/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 13:21:41 by mmcclure          #+#    #+#             */
/*   Updated: 2019/03/18 13:28:33 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_routes		*lem_routes(t_lem_in *input);


int			main()
{
	t_lem_in	*input;
	int			i;
	int			j;
	t_routes	*solved;

	input = (t_lem_in*)malloc(sizeof(t_lem_in));
	INP_NODE_C = 8;
	INP_MATRIX = (char**)malloc(sizeof(char*) * INP_NODE_C);
	i = 0;
	while (i < INP_NODE_C)
	{
		INP_MATRIX[i] = ft_strnew(INP_NODE_C);
		j = 0;
		while (j < INP_NODE_C)
		{
			INP_MATRIX[i][j] = '0';
			j++;
		}
		i++;
	}
	// INP_MATRIX[0][3] = '1';
	// INP_MATRIX[3][0] = '1';
	// INP_MATRIX[3][1] = '1';
	// INP_MATRIX[1][3] = '1';
	// INP_MATRIX[3][4] = '1';
	// INP_MATRIX[4][3] = '1';
	
	// INP_MATRIX[1][5] = '1';
	// INP_MATRIX[5][1] = '1';
	// INP_MATRIX[5][7] = '1';
	// INP_MATRIX[7][5] = '1';
	// INP_MATRIX[2][7] = '1';
	// INP_MATRIX[7][2] = '1';
	
	// INP_MATRIX[4][6] = '1';
	// INP_MATRIX[6][4] = '1';
	// INP_MATRIX[2][1] = '1';
	// INP_MATRIX[1][2] = '1';
	// INP_MATRIX[4][2] = '1';
	// INP_MATRIX[2][4] = '1';
// 2nd case
	INP_MATRIX[0][2] = '1';
	INP_MATRIX[2][0] = '1';
	INP_MATRIX[2][7] = '1';
	INP_MATRIX[7][2] = '1';
	
	INP_MATRIX[0][6] = '1';
	INP_MATRIX[6][0] = '1';
	INP_MATRIX[6][4] = '1';
	INP_MATRIX[4][6] = '1';
	INP_MATRIX[4][3] = '1';
	INP_MATRIX[3][4] = '1';
	INP_MATRIX[3][7] = '1';
	INP_MATRIX[7][3] = '1';
	
	INP_MATRIX[0][7] = '1';
	INP_MATRIX[7][0] = '1';

	
	INP_MATRIX[0][5] = '1';
	INP_MATRIX[5][0] = '1';
	INP_MATRIX[5][7] = '1';
	INP_MATRIX[7][5] = '1';
	
	INP_MATRIX[0][1] = '1';
	INP_MATRIX[1][0] = '1';
	INP_MATRIX[1][7] = '1';
	INP_MATRIX[7][1] = '1';

//print matrix
	i = -1;
	while (++i < INP_NODE_C)
		ft_putendl(INP_MATRIX[i]);
	ft_putendl(0);
//print matrix
	INP_START = 0;
	INP_END = 7;
	solved = lem_routes(input);
//print solution
	i = 0;
	while (ROU_ARR[i])
	{
		j = 0;
		while (ROU_ARR[i][j] != -1)
			ft_printf( "|%d| ", ROU_ARR[i][j++]);
		ft_putendl("");
		ft_printf( "|size = %d|\n", ROU_SIZES[i]);
		i++;
	}
	ft_printf( "|routes = %d|\n", ROU_COUN);
//print solution
	i = 0;
	while (i < INP_NODE_C)
		free(INP_MATRIX[i++]);
	i = 0;
	while (i < ROU_COUN)
			free(ROU_ARR[i++]);
	free(ROU_SIZES);
	free(ROU_ARR);
	free(solved);
	free(INP_MATRIX);
	free(input);
	return (1);
}
