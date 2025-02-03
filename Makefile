NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Source files and object files
SRCS = main.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c src/game/init.c src/game/rander.c src/input/*.c src/utils/*.c src/map/finalize_map.c src/map/validate_map.c src/map/parse_map.c src/error/*.c src/free/*.c src/game/load_text.c src/rays/raycasting.c src/rendaring/render.c
OBJS = $(SRCS:.c=.o)

# Include directories
INCLUDE_DIR = include

# Libraries
LIBFT = libft/libft.a
MLX_DIR = /home/ekechedz/minilibx
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
