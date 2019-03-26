
all: clear v
	gcc ft_ant_path.c ft_input_parsing.c ft_li_input_helpers.c ft_li_main.c ft_li_routes_helpers.c \
	ft_li_routes.c ft_solver.c lem_in.h -I ./libft/includes ./libft/libft.a -g

clear:
	rm -rf visual

v:
	gcc ./visu/visu_main.c ./visu/visu_init.c ./visu/visu_load.c ./visu/visu_render.c \
	libft/libft.a ./visu/visual_parsing.c ./visu/visual_parsing_inits.c ./visu/visual_parsing_collect_data.c \
	-I ~/Library/Frameworks/SDL2.framework/Versions/A/Headers \
	-I ~/Library/Frameworks/SDL2_image.framework/Versions/A/Headers \
	-I ~/Library/Frameworks/SDL2_ttf.framework/Versions/A/Headers \
	-F ~/Library/Frameworks/ -framework SDL2 -framework SDL2_image -framework SDL2_ttf \
	~/SDL_gfx/*.c -I ~/SDL_gfx/ -o ./visual
