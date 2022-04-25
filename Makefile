NAME			=	cub3D
SRCS			=	main.c\
					close_check.c\
					color.c\
					deal_key.c\
					draw_floor_and_ceilling.c\
					draw_wall.c\
					draw_texture.c\
					error_exit.c\
					extension_check.c\
					file_info_parse.c\
					game_free.c\
					get_next_line.c\
					get_next_line_utils.c\
					init.c\
					main_loop.c\
					make_map.c\
					map_check.c\
					move_and_collision.c\
					read_file.c\
					is_empty_line.c\
					color_atoi.c\
					set_texture.c\
					set_color.c\
					parse_check.c\
					utils.c

OBJS_DIR		=	./objs
OBJS			=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

CC				=	gcc -g
CFLAGS			=	-Wall -Wextra -Werror
INCLUDE			=	-I./include -I/usr/include -I./mlx_linux
MINI			=	-Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm
LIBFT			=	-Llibft -lft
RM				=	rm -f

.PHONY			:	all clean fclean re

#VPATH		=	srcs:srcs/game:srcs/init:srcs/map:srcs/utils

vpath %.c srcs:srcs/game:srcs/init:srcs/map:srcs/utils
vpath %.h include

all				:	$(NAME)

$(NAME)			:	$(OBJS)
					make -C mlx_linux
					make -C libft
					$(CC) $(CFLAGS) $(OBJS) $(MINI) $(LIBFT) -o $@

$(OBJS_DIR)/%.o	:	%.c
					$(CC) $(CFLAGS) $(INCLUDE) -O3 -c $< -o $@

clean			:
					make clean -C libft
					$(RM) $(OBJS)

fclean			:
					make fclean -C libft
					$(RM) $(OBJS) $(NAME) 

re				:	fclean all
