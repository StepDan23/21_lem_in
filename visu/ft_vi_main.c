/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vi_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:16:13 by mmcclure          #+#    #+#             */
/*   Updated: 2019/03/23 15:28:45 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/visu.h"

t_visu		*window_init(void)
{
	t_visu	*window;

	window = (t_visu*)malloc(sizeof(t_visu));
	WIN_WIN = NULL;
	WIN_BACK = NULL;
	WIN_QUIT = 0;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		ft_printf("Init_Error: %s\n", SDL_GetError());
		return (NULL);
	}
	WIN_WIN = SDL_CreateWindow("Vizualizer", SDL_WINDOWPOS_UNDEFINED,\
	SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (WIN_WIN == NULL)
	{
		ft_printf("Init_Window_Error: %s\n", SDL_GetError());
		return (NULL);
	}
	WIN_REND = SDL_CreateRenderer(WIN_WIN, -1, SDL_RENDERER_ACCELERATED);
	if (WIN_REND == NULL)
	{
		ft_printf("Init_Renderer_Error: %s\n", SDL_GetError());
		return (NULL);
	}
	return (window);
}

void		window_close(t_visu *window)
{
	if (WIN_BACK != NULL)
	{
		SDL_DestroyTexture(WIN_BACK);
		WIN_BACK = NULL;
	}
	if (WIN_ANT != NULL)
	{
		SDL_DestroyTexture(WIN_ANT);
		WIN_ANT = NULL;
	}
	SDL_DestroyWindow(WIN_WIN);
	WIN_WIN = NULL;
	SDL_Quit();
}

void	modify_back(SDL_Surface *back, SDL_Surface *box)
{
	SDL_Rect	box_rect;
	SDL_Rect	srs_rect;
	SDL_Surface	*scaled;

	int ants = 10;
	scaled = SDL_CreateRGBSurface(0, 600, 450, 32,
				0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
	srs_rect.x = 0;
	srs_rect.y = 0;
	srs_rect.w = 142;
	srs_rect.h = 142;
	box_rect = srs_rect;
	box_rect.w *= 2;
	box_rect.h *= 2;
	SDL_BlitScaled(box, &srs_rect, scaled, &box_rect);
	SDL_SetSurfaceAlphaMod(scaled, 100);
	while (ants)
	{
		srs_rect.x = 200;
		srs_rect.y = 200;
		SDL_BlitSurface(scaled, &box_rect, back, &srs_rect);
		ants--;
	}
	SDL_FreeSurface(scaled);
}

int		load_textures(t_visu *window)
{
	SDL_Surface		*surf_back;
	SDL_Surface		*surf_ant;
	SDL_Surface		*box;

	surf_back = SDL_LoadBMP("visu/background.bmp");
	box = IMG_Load("visu/box.png");
	surf_ant = IMG_Load("visu/foo.png");
	if (surf_ant == NULL || surf_back == NULL || box == NULL)
	{
		ft_printf("Load_Error: %s\n", SDL_GetError());
		return (0);
	}
	modify_back(surf_back, box);
	WIN_BACK = SDL_CreateTextureFromSurface(WIN_REND, surf_back);
	WIN_ANT = SDL_CreateTextureFromSurface(WIN_REND, surf_ant);
	if (WIN_BACK == NULL || WIN_ANT == NULL)
	{
		ft_printf("Texture_Error: %s\n", SDL_GetError());
	}
	SDL_FreeSurface(surf_back);
	SDL_FreeSurface(surf_ant);
	return (1);
}

void		render_back(t_visu *window)
{
	SDL_Rect	clip_area;

	clip_area.x = 0;
	clip_area.y = 0;
	clip_area.w = SCREEN_WIDTH;
	clip_area.h = SCREEN_HEIGHT;
	SDL_RenderCopy(WIN_REND, WIN_BACK, NULL, &clip_area);
}

void		render_ant(t_visu *window, int x, int y, int angle, int frame)
{
	SDL_Rect	render_area;
	SDL_Rect	clip_area;

	clip_area.x = 0;
	clip_area.w = 847;
	clip_area.h = 1070;
	if (frame == 0 || frame == 2)
		clip_area.y = 2384;
	else if (frame == 1)
		clip_area.y = 1238;
	else
		clip_area.y = 126;
	render_area.x = x;
	render_area.y = y;
	render_area.w = 216;
	render_area.h = 300;
	SDL_RenderCopyEx(WIN_REND, WIN_ANT, &clip_area, &render_area, angle, NULL, SDL_FLIP_NONE);
}

// void		render_window(t_visu *window)
// {
// 	int		frame;

// 	frame = 0;
// 	while (!WIN_QUIT)
// 	{
// 		while (SDL_PollEvent(&e) != 0)
// 		{
// 			if (e.type == SDL_QUIT)
// 				WIN_QUIT = 1;
// 			if (e.type == SDL_KEYDOWN)
// 			{
// 				if (e.key.keysym.sym == SDLK_ESCAPE)
// 					WIN_QUIT = 1;
// 			}
// 		}
// 		SDL_RenderClear(WIN_REND);
// 		x += 3 * a;
// 		y += 3 * b;
// 		if (x + 216 > SCREEN_WIDTH || x < 0)
// 			a *= -1;
// 		if (y + 300 > SCREEN_HEIGHT || y  < 0)
// 			b *= -1;
// 		frame += (frame > 27) ? -frame : 1;
// 		render_back(window);
// 		render_ant(window, x, y, 135, frame / 7);
// 		SDL_RenderPresent(WIN_REND);
// 		SDL_Delay(10);
		
// 	}
// }

int		main(void)
{
	t_visu		*window;
	SDL_Event	e;
	int		frame = 0;
	int			x = 0;
	int			y = 0;
	int a = 1;
	int b = 1;

	if (!(window = window_init()))
		return (0);
	load_textures(window);
	while (!WIN_QUIT)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				WIN_QUIT = 1;
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_ESCAPE)
					WIN_QUIT = 1;
			}
		}
		SDL_RenderClear(WIN_REND);
		x += 3 * a;
		y += 3 * b;
		if (x + 216 > SCREEN_WIDTH || x < 0)
			a *= -1;
		if (y + 300 > SCREEN_HEIGHT || y  < 0)
			b *= -1;
		frame += (frame > 27) ? -frame : 1;
		render_back(window);
		render_ant(window, x, y, 135, frame / 7);
		SDL_RenderPresent(WIN_REND);
		SDL_Delay(10);
		
	}
	window_close(window);
	return (1);
}
