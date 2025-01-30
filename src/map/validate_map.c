#include "../../include/cub3d.h"

static int is_valid_map_char(char c)
{
	// Valid characters inside the map: '0', '1', 'N', 'S', 'E', 'W'
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

static void validate_map_characters(t_config *config)
{
	int i = 0;
	int j = 0;

	while (i < config->map->height)
	{
		j = 0;
		while (j < config->map->width)
		{
			char c = config->map->grid[i][j];
           // printf("Validating char '%c' at position (%d, %d)\n", c, i, j);

			// If the character is invalid, print the invalid character and position, then exit
			if (!is_valid_map_char(c))
			{
				printf("Invalid char '%c' at position (%d, %d)\n", c, i, j);
				exit_with_error("Error: Invalid character in the map", 1);
			}
			j++;
		}
		i++;
	}
}

static int is_map_surrounded_by_walls(t_config *config)
{
	int i, j;
	j = 0;
	while (j < config->map->width)
	{
		if (config->map->grid[0][j] != '1' && config->map->grid[0][j] != ' ')
		{
			printf("Error: Top row not surrounded by walls at (%d, %d)\n", 0, j);
			return 0;
		}
		if (config->map->grid[config->map->height - 1][j] != '1' && config->map->grid[config->map->height - 1][j] != ' ')
		{
			printf("Error: Bottom row not surrounded by walls at (%d, %d)\n", config->map->height - 1, j);
			return 0;
		}
		j++;
	}
	i = 0;
	while(i < config->map->height)
	{
		j = 0;
		while (config->map->grid[i][j] == ' ')
			j++;
		if (config->map->grid[i][j] != '1')
		{
			printf("Error: Left side not enclosed at (%d, %d)\n", i, j);
			return 0;
		}
		j = config->map->width - 1;
		while (j > 0 && config->map->grid[i][j] == ' ')
			j--;
		if (config->map->grid[i][j] != '1')
		{
			printf("Error: Right side not enclosed at (%d, %d)\n", i, j);
			return 0;
		}
		i++;
	}
	return 1;
}


static int check_player_start(t_config *config)
{
	int player_count = 0;
	int i = 0;
	int j = 0;

	while (i < config->map->height)
	{
		j = 0;
		while (j < config->map->width)
		{
			if (config->map->grid[i][j] == 'N' || config->map->grid[i][j] == 'S' ||
				config->map->grid[i][j] == 'E' || config->map->grid[i][j] == 'W')
			{
				player_count++;
				if (player_count > 1)
					return 0;
			}
			j++;
		}
		i++;
	}

	return (player_count == 1); // Return true if exactly one player start is found
}

void validate_map(t_config *config)
{
	validate_map_characters(config);
	if (!is_map_surrounded_by_walls(config))
		exit_with_error("Error: Map is not surrounded by walls", 1);
	if (!check_player_start(config))
		exit_with_error("Error: Invalid or multiple player start positions", 1);
}
