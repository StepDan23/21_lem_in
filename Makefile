# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmcclure <mmcclure@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/27 13:52:16 by mmcclure          #+#    #+#              #
#    Updated: 2019/04/28 13:01:15 by mmcclure         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1 = lem-in-hex

NAME2 = visu-hex

LIB = ./libft/libft.a

LIB_GFX = ~/SDL_gfx/libsdl_gfx.a

SRCS_LEM_F = ft_ant_path.c ft_input_parsing.c ft_li_input_helpers.c ft_li_main.c \
	ft_li_routes_helpers.c ft_li_routes.c ft_solver.c

SRCS_VISU_F = visu_main.c visu_init.c visu_load.c visu_render.c visual_parsing.c \
	visual_parsing_inits.c visual_parsing_collect_data.c visu_print.c visu_events.c

HEADERS = -I ~/Library/Frameworks/SDL2.framework/Versions/A/Headers \
	-I ~/Library/Frameworks/SDL2_image.framework/Versions/A/Headers \
	-I ~/Library/Frameworks/SDL2_ttf.framework/Versions/A/Headers \
	-I ~/SDL_gfx/

FRAMEWORKS = -F ~/Library/Frameworks/ -framework SDL2 -framework SDL2_image \
	-framework SDL2_ttf

LEM_DIR = ./lem_in/

VISU_DIR = ./visu/

FLAGS = -Wall -Wextra -Werror

SRCS_LEM = $(addprefix $(LEM_DIR), $(SRCS_LEM_F))

SRCS_VISU = $(addprefix $(VISU_DIR), $(SRCS_VISU_F))

all: $(NAME1) $(NAME2)

$(NAME1): $(LIB) $(LIB_GFX)
	gcc $(SRCS_LEM) $(LIB) $(FLAGS) -o $(NAME1)

$(NAME2): $(LIB) 
	gcc $(SRCS_VISU) $(LIB) $(HEADERS) $(LIB_GFX) $(FRAMEWORKS) $(FLAGS) -o $(NAME2)

$(LIB):
	make -C libft/

$(LIB_GFX):
	gcc -c ~/SDL_gfx/*.c -F ~/Library/Frameworks/
	ar rcs $(LIB_GFX) SDL2_framerate.o SDL2_gfxPrimitives.o SDL2_imageFilter.o SDL2_rotozoom.o
	ranlib $(LIB_GFX)

clean:
	make -C libft/ clean
	rm -f SDL2_framerate.o SDL2_gfxPrimitives.o SDL2_imageFilter.o SDL2_rotozoom.o

fclean:
	rm -f $(NAME1) $(NAME2) $(LIB_GFX)
	make -C libft/ fclean

re: fclean all

rr:
	rm -f $(NAME2)
	make
