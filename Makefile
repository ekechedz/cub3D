NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Source files and object files
SRCS = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c src/1_init_structs/init.c src/1_init_structs/init2.c src/2_main/main.c src/utils/utils.c src/utils/parse_utils.c src/utils/map_utils.c src/utils/map_utils1.c src/map/validate_map.c src/map/parse_map.c src/0_error/exit_erro.c src/free/*.c src/game/load_text.c src/rays/raycasting.c src/rendering/render.c src/map/mini_map.c src/move/player_move.c src/textures.c src/3_start_events/events.c src/map/parse_line.c
OBJS = $(SRCS:.c=.o)

# Include directories
INCLUDE_DIR = include

# Libraries
LIBFT = libft/libft.a
MLX_DIR = /home/ekechedz/minilibx
#MLX_DIR = /home/natalia/Repositories/minilibx #for home
#MLX_DIR = /home/nleite-s/Repositories/cub3d/minilibx
MLX = $(MLX_DIR)/libmlx.a

# Linker flags for MiniLibX
LDFLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX) $(LDFLAGS)

# Build libft
$(LIBFT):
	make -C libft

# Build MiniLibX
$(MLX):
	make -C $(MLX_DIR)

# Clean object files
clean:
	rm -f $(OBJS)
	make -C libft clean
	make -C $(MLX_DIR) clean

# Clean everything
fclean: clean
	rm -f $(NAME)
	make -C libft fclean

# Rebuild everything
re: fclean all
