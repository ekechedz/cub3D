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
		exit (1);
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
	printf("Floor Color: %ls\n", config->floor_color);
	printf("Ceiling Color: %ls\n", config->ceiling_color);

}

void print_game(t_game *game)
{
	printf("\nGame Data:\n");

	// Print the map data
	printf("Map Height: %d\n", game->config->map->height);
	printf("Map Width: %d\n", game->config->map->width);

	// Print the floor and ceiling color values
	printf("Floor Color: %ls\n", game->config->floor_color);
	printf("Ceiling Color: %ls\n", game->config->ceiling_color);
	printf("Floor color: 0x%06X\n", *game->floor_color); // Dereferencing to get the color value
	printf("Ceiling color: 0x%06X\n", *game->ceiling_color);
}


int	main(int argc, char **argv)
{
	t_game		*game;
	t_config	*config;

	check_input(argc, argv);

	config = init_config();
	if (!config)
	{
		write(2, "Failed to initialize configuration\n", 35);
		return (1);
	}
	if (!parse_cub_file(argv[1], config)) //in case of error, i already free config inside
	{
		write(2, "Failed to parse .cub file\n", 26); 
		return (1);
	}
	print_config(config);
	game = init_game(config);
	if (!game)
	{
		write(2, "Failed to initialize game\n", 26);
		free_game(game);
		return (1);
	}
	print_game(game);
	if (load_textures(game, config) < 0)
	{
		fprintf(stderr, "Error: Failed to load textures\n");
		free_game(game);
		return (1);
	}
	//free_config(config);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D Test Window");
	if (!game->win)
	{
		write(2, "Window creation failed\n", 23);
		free_game(game);
		return 1;
	}

	init_events(game);
	mlx_loop(game->mlx);

	// Clean up resources if necessary
	return 0;
}

void	init_events(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	memset(game->key_st, 0, sizeof(game->key_st)); //maybe in init_game is better
	
	mlx_hook(game->win, 2, 1L << 0, key_hook, game);
	mlx_hook(game->win, 3, 1L << 1, key_release_hook, game);
	//then theres a mlx_hook with a handle_close function 
	//then a mlx_hook with a handle_mouse_move that im not sure we need for mandatory
	//then a mlx_hook with a handle_mouse_click
	mlx_loop_hook(game->mlx, main_loop, game);
	//then mlx_mouse_move
	//then mlx_mouse_hide
}