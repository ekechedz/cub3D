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

// void test_parse_map(t_game *game, const char *file_path)
// {
// 	init_config(game);  // Initialize the game structure// Initialize the config

// 	// Parse the .cub file
// 	config = parse_cub_file(file_path, config);

// 	// Assign the parsed map to the game
// 	game->map = config->map;

// 	// Print the parsed map to verify it's loaded correctly
// 	printf("Map Dimensions: Width = %d, Height = %d\n", game->map->width, game->map->height);

// 	// Print the map grid for debugging
// 	for (int y = 0; y < game->map->height; y++)
// 	{
// 		for (int x = 0; x < game->map->width; x++)
// 		{
// 			printf("%c", game->map->grid[y][x]);
// 		}
// 		printf("\n");
// 	}

// 	// Free the config after use
// 	free(config);
// }

void print_config(t_config *config)
{
	printf("Config Data:\n");

	// Print the map data
	printf("Map Height: %d\n", config->map->height);
	printf("Map Width: %d\n", config->map->width);

	// Print the textures paths
	printf("Textures:\n");
	// printf("North Texture: %s\n", config->textures->north->buff);
	printf("South Texture: %s\n", config->textures->south->buff);
	printf("East Texture: %s\n", config->textures->east->buff);
	printf("West Texture: %s\n", config->textures->west->buff);
	printf("Floor Texture: %s\n", config->textures->floor->buff);
	printf("Ceiling Texture: %s\n", config->textures->ceiling->buff);
	printf("Door Texture: %s\n", config->textures->door->buff);
	printf("Gameover Texture: %s\n", config->textures->gameover->buff);

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

	// Print the textures paths
	printf("Textures:\n");
	printf("North Texture: %s\n", game->config->textures->north->buff);
	printf("South Texture: %s\n", game->config->textures->south->buff);
	printf("East Texture: %s\n", game->config->textures->east->buff);
	printf("West Texture: %s\n", game->config->textures->west->buff);
	printf("Floor Texture: %s\n", game->config->textures->floor->buff);
	printf("Ceiling Texture: %s\n", game->config->textures->ceiling->buff);

	// Print the floor and ceiling color values
	printf("Floor Color: %d\n", game->config->floor_color);
	printf("Ceiling Color: %d\n", game->config->ceiling_color);
}

int main(int argc, char **argv)
{
	t_game *game = (t_game *)malloc(sizeof(t_game));
	t_config *config = (t_config *)malloc(sizeof(t_config));

	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("Current working directory: %s\n", cwd);
	}
	else
	{
		perror("getcwd error");
	}

	// Check input validity
	if (check_input(argc, argv) < 0)
		return 1;

	// Initialize the configuration
	init_config(config); // Initialize the configuration structure
	if (!config)
	{
		write(2, "Failed to initialize configuration\n", 35);
		return 1;
	}

	// Initialize the map structure
	config->map = init_map(0, 0);
	if (!config->map)
	{
		write(2, "Failed to initialize map\n", 25);
		free_config(config);
		return 1;
	}

	// Parse the .cub file
	if (!parse_cub_file(argv[1], config))
	{
		write(2, "Failed to parse .cub file\n", 26);
		free_config(config);
		return 1;
	}
	print_config(config);
	// Initialize the game structure
	init_game(game, config);
	if (!game)
	{
		write(2, "Failed to initialize game\n", 26);
		free_config(config);
		return 1;
	}
	print_game(game);
	// test_parse_map(game, argv[1]);
	if (load_textures(game, config) < 0)
	{
		fprintf(stderr, "Error: Failed to load textures\n");
		return (1);
	}

	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D Test Window");
	if (!game->win)
	{
		write(2, "Window creation failed\n", 23);
		free_game(game);
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
