/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 18:24:58 by mmcclure          #+#    #+#             */
/*   Updated: 2019/03/27 10:53:29 by mmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/visu.h"

static void		print_str(t_window *window,
						char *str, SDL_Rect *src, SDL_Rect *dst)
{
	SDL_Surface		*text_surf;
	SDL_Texture		*text;
	SDL_Color		color;

	color = (SDL_Color){255, 255, 255, 255};
	text_surf = TTF_RenderText_Blended(FONT_STAT, str, color);
	text = SDL_CreateTextureFromSurface(WIN_REND, text_surf);
	SDL_FreeSurface(text_surf);
	SDL_RenderCopy(WIN_REND, text, src, dst);
	SDL_DestroyTexture(text);
}

void			print_status(t_window *window, t_rend *render, int len)
{
	SDL_Rect	src;
	SDL_Rect	dst;
	char		*str;
	int			num;

	src = (SDL_Rect){0, 0, 350, F_STAT + 2};
	dst = (SDL_Rect){400, 0, 350, F_STAT + 2};
	print_str(window, "At the start:                  At the end:", &src, &dst);
	num = ANTS_START;
	while ((num /= 10) > 0)
		len++;
	src = (SDL_Rect){0, 0, 16 * len, F_STAT + 2};
	dst = (SDL_Rect){450, F_STAT, 17 * len, F_STAT + 2};
	str = ft_itoa(ANTS_START);
	print_str(window, str, &src, &dst);
	free(str);
	len = 1;
	num = ANTS_END;
	while ((num /= 10) > 0)
		len++;
	src = (SDL_Rect){0, 0, 16 * len, F_STAT + 2};
	dst = (SDL_Rect){680, F_STAT, 17 * len, F_STAT + 2};
	str = ft_itoa(ANTS_END);
	print_str(window, str, &src, &dst);
	free(str);
}
