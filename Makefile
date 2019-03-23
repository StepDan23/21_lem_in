
all: clear visual
	gcc ft_ant_path.c ft_input_parsing.c ft_li_input_helpers.c ft_li_main.c ft_li_routes_helpers.c \
	ft_li_routes.c ft_solver.c lem_in.h -I ./libft/includes ./libft/libft.a -g

visual:
	gcc visual_parsing.c -I ./libft/includes ./libft/libft.a -o visual

clear:
	rm -rf visual

v:
	gcc ./visu/ft_vi_main.c libft/libft.a \
	-I ~/Library/Frameworks/SDL2.framework/Versions/A/Headers \
	-F ~/Library/Frameworks/ -framework SDL2 \
	-I ~/Library/Frameworks/SDL2_image.framework/Versions/A/Headers \
	-F ~/Library/Frameworks/ -framework SDL2 -framework SDL2_image \
