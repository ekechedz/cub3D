NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = src/main.c src/game/*.c  src/input/*.c 
OBJS = $(SRCS:.c=.o)
LIBFT = libft/libft.a
MLX = mlx/mlx.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX) -lX11 -lXext -lm

$(LIBFT):
	make -C libft

$(MLX):
	make -C mlx

clean:
	rm -f $(OBJS)
	make -C libft clean
	make -C mlx clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all
