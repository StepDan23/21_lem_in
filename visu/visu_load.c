/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 14:15:11 by mmcclure          #+#    #+#             */
/*   Updated: 2019/03/25 19:34:44 by mmcclure         ###   ########.fr       */
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

static void		box_names_on_back(SDL_Surface *back, SDL_Surface *box,
										t_prop *map, t_window *window)
{
	SDL_Rect	box_rect;
	SDL_Rect	srs_rect;
	SDL_Rect	text_rect;
	SDL_Surface	*text;
	int			nodes;

	nodes = MAP_NODE_C;
	box_rect = (SDL_Rect){0, 0, BOX_WIDTH, BOX_HEIGHT};
	surf_scale(&box, &box_rect, MAP_SCALE);
	while (nodes)
	{
		srs_rect.x = MAP_COORDS[nodes - 1][0] * MAP_SCALE - box_rect.w / 2;
		srs_rect.y = MAP_COORDS[nodes - 1][1] * MAP_SCALE - box_rect.h / 2;
		SDL_BlitSurface(box, &box_rect, back, &srs_rect);
		text = TTF_RenderText_Blended(WIN_FONT, MAP_NAMES[nodes - 1],
											(SDL_Color){255, 255, 255, 200});
		srs_rect.y += box_rect.h;
		srs_rect.x += box_rect.h / 2.5;
		srs_rect.w = box_rect.w / 1.5;
		srs_rect.h = box_rect.h / 3;
		text_rect = (SDL_Rect){0, 0, 150 , 42};
		SDL_BlitScaled(text, &text_rect, back, &srs_rect);
		SDL_FreeSurface(text);
		nodes--;
	}
	SDL_FreeSurface(box);
}

void		tubes_on_back(t_window *window, t_prop *map)
{
	SDL_Point	lines[2];
	int			nodes;
	int			i;
	SDL_Texture		*trans;

	nodes = MAP_NODE_C - 1;
	WIN_TUBES =  SDL_CreateTexture(WIN_REND, SDL_PIXELFORMAT_RGBA8888, 
					SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderTarget(WIN_REND, WIN_TUBES);
	SDL_RenderCopy(WIN_REND, WIN_BACK, NULL, NULL);
	SDL_RenderSetScale(WIN_REND, MAP_SCALE, MAP_SCALE);
	while (nodes >= 0)
	{
		i = 0;
		lines[0].x = MAP_COORDS[nodes][0];
		lines[0].y = MAP_COORDS[nodes][1];
		while (i < MAP_NODE_C)
		{
			if (MAP_MATRIX[nodes][i] == '1')
			{
				lines[1].x = MAP_COORDS[i][0];
				lines[1].y = MAP_COORDS[i][1];
				thickLineRGBA (WIN_REND, MAP_COORDS[nodes][0], MAP_COORDS[nodes][1],
							MAP_COORDS[i][0], MAP_COORDS[i][1], 5, 101, 67, 33, 40);
			}
			i++;
		}
		nodes--;
	}
	SDL_SetRenderTarget(WIN_REND, NULL);
}

int				load_files(t_window *window, t_prop *map)
{
	SDL_Surface		*surf_back;
	SDL_Surface		*box;
	SDL_Surface		*surf_ant;

	surf_back = SDL_LoadBMP("visu/img/background.bmp");
	box = IMG_Load("visu/img/box.png");
	surf_ant = IMG_Load("visu/img/foo.png");
	WIN_FONT = TTF_OpenFont("visu/fonts/Aller_BdIt.ttf", 40);
	if (!surf_back || !box || !surf_ant || !WIN_FONT)
		return (ft_printf("Load_Error: %s\n", SDL_GetError()));
	box_names_on_back(surf_back, box, map, window);
	WIN_BACK = SDL_CreateTextureFromSurface(WIN_REND, surf_back);
	WIN_ANT = SDL_CreateTextureFromSurface(WIN_REND, surf_ant);
	if (WIN_BACK == NULL || WIN_ANT == NULL )
		return (ft_printf("Texture_Error: %s\n", SDL_GetError()));
	tubes_on_back(window, map);
	SDL_FreeSurface(surf_back);
	SDL_FreeSurface(surf_ant);
	return (0);
}
