#include "libft/libft.h"
#include "include/cub3d.h"

char *check_file(char *filename)
{
	int len;
	int i;

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
int handle_key_press(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		mlx_loop_end(game->mlx);
	return 0;
}

int handle_close(t_game *data)
{
	mlx_loop_end(data->mlx);
	return (0);
}

int close_window(void *param)
{
	mlx_destroy_window(param, param); // Close the window
	exit(0);
	return (0);
}

void print_config(t_config *config)
{
	printf("Config Data:\n");

	// Print the map data
	printf("Map Height: %d\n", config->map->height);
	printf("Map Width: %d\n", config->map->width);



	// Print the floor and ceiling color values
	printf("Floor Color: %d\n", config->floor_color);
	printf("Ceiling Color: %d\n", config->ceiling_color);
}

void print_game(t_game *game)
{
	printf("\nGame Data:\n");

	// Print the map data
	printf("Map Height: %d\n", game->config->map->height);
	printf("Map Width: %d\n", game->config->map->width);

	// Print the floor and ceiling color values
	printf("Floor Color: %d\n", game->config->floor_color);
	printf("Ceiling Color: %d\n", game->config->ceiling_color);
}

int main(int argc, char **argv)
{
	t_game *game;
	t_config *config;

	if (!game || !config) // Check malloc success
	{
		write(2, "Failed to allocate memory\n", 25);
		return 1;
	}

	// Check input validity
	if (check_input(argc, argv) < 0)
	{
		free_config(config);
		free(game);
		return 1;
	}
	config = init_config();
	if (!config)
	{
		free(game);
		write(2, "Failed to initialize configuration\n", 35);
		return 1;
	}
	config->map = init_map(0, 0); //i think this should be inside of init_config
	if (!config->map)
	{
		write(2, "Failed to initialize map\n", 25);
        free(game);
		free_config(config);
		return 1;
	}
	if (!parse_cub_file(argv[1], config))
	{
		write(2, "Failed to parse .cub file\n", 26);
		free(game);
		free_config(config);
		return 1;
	}
	print_config(config);
	game = init_game(config);
	if (!game)
	{
		write(2, "Failed to initialize game\n", 26);
		free_config(config);
		//free(game);
		return 1;
	}
	print_game(game);
	if (load_textures(game, config) < 0)
	{
		fprintf(stderr, "Error: Failed to load textures\n");
		free_config(config);
        //free(game);
		return (1);
	}
	//free_config(config);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D Test Window");
	if (!game->win)
	{
		write(2, "Window creation failed\n", 23);
		//free_game(game);
		return 1;
	}

	mlx_clear_window(game->mlx, game->win);
	mlx_string_put(game->mlx, game->win, 200, 200, 0xFFFFFF, "Hello, MiniLibX!");
	mlx_hook(game->win, 17, 0L, close_window, game->mlx);

	// Start the game loop
	mlx_loop(game->mlx);

	// Clean up resources if necessary
	return 0;
}
