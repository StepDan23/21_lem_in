/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 14:15:11 by mmcclure          #+#    #+#             */
/*   Updated: 2019/03/24 19:15:29 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/visu.h"

static void		surf_scale(SDL_Surface **surf, SDL_Rect *src_rect, float scale)
{
	SDL_Surface	*scaled;
	SDL_Rect	sca_rect;

	scaled = SDL_CreateRGBSurface(0, 600, 450, 32,
				0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
	sca_rect = *src_rect;
	sca_rect.w *= scale;
	sca_rect.h *= scale;
	SDL_BlitScaled(*surf, src_rect, scaled, &sca_rect);
	SDL_SetSurfaceAlphaMod(scaled, 150);
	SDL_FreeSurface(*surf);
	*surf = scaled;
	*src_rect = sca_rect;
}

static void		modify_back(SDL_Surface *back, SDL_Surface *box, t_prop *map)
{
	SDL_Rect	box_rect;
	SDL_Rect	srs_rect;
	int			nodes;

	nodes = MAP_NODE_C;
	box_rect = (SDL_Rect){0, 0, BOX_WIDTH, BOX_HEIGHT};
	surf_scale(&box, &box_rect, MAP_SCALE);
	while (nodes)
	{
		srs_rect.x = MAP_MATRIX[nodes - 1][0] * MAP_SCALE - box_rect.w / 2;
		srs_rect.y = MAP_MATRIX[nodes - 1][1] * MAP_SCALE - box_rect.h / 2;
		SDL_BlitSurface(box, &box_rect, back, &srs_rect);
		//name
		nodes--;
	}
	SDL_FreeSurface(box);
}

int				load_files(t_window *window, t_prop *map)
{
	SDL_Surface		*surf_back;
	SDL_Surface		*box;
	SDL_Surface		*surf_ant;

	surf_back = SDL_LoadBMP("visu/background.bmp");
	box = IMG_Load("visu/box.png");
	surf_ant = IMG_Load("visu/foo.png");
	if (!surf_back || !box || !surf_ant)
	{
		ft_printf("Load_Error: %s\n", SDL_GetError());
		return (0);
	}
	modify_back(surf_back, box, map);
	WIN_BACK = SDL_CreateTextureFromSurface(WIN_REND, surf_back);
	WIN_ANT = SDL_CreateTextureFromSurface(WIN_REND, surf_ant);
	if (WIN_BACK == NULL || WIN_ANT == NULL )
	{
		ft_printf("Texture_Error: %s\n", SDL_GetError());
		return (0);
	}
	SDL_FreeSurface(surf_back);
	SDL_FreeSurface(surf_ant);
	return (1);
}
