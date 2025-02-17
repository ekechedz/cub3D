NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

GNL_D = get_next_line
GNL_S = $(GNL_D)/get_next_line.c $(GNL_D)/get_next_line_utils.c
UTILS_D = src/1_utils
UTILS_S = $(UTILS_D)/map_utils.c $(UTILS_D)/map_utils1.c $(UTILS_D)/parse_utils.c $(UTILS_D)/utils.c
INIT_D = src/2_init
INIT_S = $(INIT_D)/init.c $(INIT_D)/init2.c
MAIN_D = src/3_main
MAIN_S = $(MAIN_D)/main.c
EVENT_D = src/3_start_events
EVENT_S = $(EVENT_D)/events.c
MAP_D = src/4_map
MAP_S = $(MAP_D)/mini_map.c $(MAP_D)/parse_line.c $(MAP_D)/parse_map.c $(MAP_D)/validate_map.c
TXT_D = src/5_textures
TXT_S = $(TXT_D)/load_text.c $(TXT_D)/textures.c
RAY_D = src/6_rays
RAY_S = $(RAY_D)/raycasting.c
RENDER_D = src/7_rendering
RENDER_S = $(RENDER_D)/render.c
MOVE_D = src/8_move
MOVE_S = $(MOVE_D)/player_move.c
FREE_D = src/9_free
FREE_S = $(FREE_D)/free.c $(FREE_D)/free2.c

SRCS = $(GNL_S) $(UTILS_S) $(INIT_S) $(MAIN_S) $(EVENT_S) $(MAP_S) $(TXT_S) $(RAY_S) $(RENDER_S) $(MOVE_S) $(FREE_S)
OBJS = $(SRCS:.c=.o)

INCLUDE_DIR = include

LIBFT = libft/libft.a
#MLX_DIR = /home/ekechedz/minilibx
MLX_DIR = /home/nleite-s/Repositories/cub3d/minilibx
MLX = $(MLX_DIR)/libmlx.a

LDFLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX) $(LDFLAGS)

$(LIBFT):
	make -C libft

$(MLX):
	make -C $(MLX_DIR)

clean:
	rm -f $(OBJS)
	make -C libft clean
	make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all
