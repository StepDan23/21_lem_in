
all: clear visual
	gcc ft_ant_path.c ft_input_parsing.c ft_li_input_helpers.c ft_li_main.c ft_li_routes_helpers.c \
	ft_li_routes.c ft_solver.c lem_in.h -I ./libft/includes ./libft/libft.a -g

visual:
	gcc visual_parsing.c -I ./libft/includes ./libft/libft.a -o visual

clear:
	rm -rf visual