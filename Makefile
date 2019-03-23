
all:
	gcc *.c lem_in.h -I ./libft/includes ./libft/libft.a
	
v:
	gcc ./visu/ft_vi_main.c libft/libft.a \
	-I ~/Library/Frameworks/SDL2.framework/Versions/A/Headers \
	-F ~/Library/Frameworks/ -framework SDL2 \
	-I ~/Library/Frameworks/SDL2_image.framework/Versions/A/Headers \
	-F ~/Library/Frameworks/ -framework SDL2 -framework SDL2_image \
