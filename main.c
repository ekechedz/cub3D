#include "libft/libft.h"
#include "include/cub3d.h"

char	*check_file(char *filename)
{
	int		len;
	int		i;

	len = ft_strlen(filename);
	i = fmax(len - 5, 0);
	while (filename[i] != '.' && filename[i] != '\0')
		i++;
	return (filename + i);
}


int check_input(int ac, char **av)
{
	if (ac != 2 || ft_strncmp(check_file(av[1]), ".cub", 5) != 0)
	{
		ft_putendl_fd("Usage: ./cub3d file.cub", 2);
		return (-1);
	}
	return (0);
}
int	handle_key_press(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		mlx_loop_end(game->mlx);
	return 0;
}

int	handle_close(t_game *data)
{
	mlx_loop_end(data->mlx);
	return (0);
}

int main(int argc, char **argv)
{
    t_game *game;
    if (check_input(argc, argv) < 0)
		return 1;
    init_game(game);

	t_config *config = malloc(sizeof(t_config));
	ft_memset(config, 0, sizeof(t_config));
	config->map = malloc(sizeof(t_map));
	config = parse_cub_file(argv[1], config);
    game->map = config->map;
    game->floor_color = config->floor_color;
    game->ceiling_color = config->ceiling_color;
    game->textures = config->textures;
    free(config);

    // Start the game loop (render and input handling)
    mlx_loop_hook(game->mlx, render_frame_wrapper, &game);
    mlx_key_hook(game->win, handle_input_wrapper, &game);
	mlx_hook(game->win, KeyPress, KeyPressMask, &handle_key_press, &game);
	mlx_hook(game->win, DestroyNotify, StructureNotifyMask,
		&handle_close, &game);
    // Run the MLX event loop
    mlx_loop(game->mlx);

    // Clean up resources
    //cleanup(&game);

    return 0;
}
