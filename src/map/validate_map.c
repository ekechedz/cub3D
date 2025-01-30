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
            printf("Validating char '%c' at position (%d, %d)\n", c, i, j);

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
	int i = 0;
	int j = 0;

	while (i < config->map->height)
	{
		j = 0;
		while (j < config->map->width)
		{
			// Check if the top and bottom rows are completely walls
			if ((i == 0 || i == config->map->height - 1) && config->map->grid[i][j] != '1')
				return 0; // Invalid if there is no wall
			// Check if the left and right columns are completely walls
			if ((j == 0 || j == config->map->width - 1) && config->map->grid[i][j] != '1')
				return 0; // Invalid if there is no wall
			j++;
		}
		i++;
	}
	return 1; // Map is surrounded by walls
}

static int check_player_start(t_config *config)
{
	int player_count = 0;
	int i = 0;
	int j = 0;

	// Scan the map to count player start positions (N, S, E, W)
	while (i < config->map->height)
	{
		j = 0;
		while (j < config->map->width)
		{
			if (config->map->grid[i][j] == 'N' || config->map->grid[i][j] == 'S' ||
				config->map->grid[i][j] == 'E' || config->map->grid[i][j] == 'W')
			{
				player_count++;
				if (player_count > 1) // If more than one player start, return false
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
	validate_map_characters(config);		 // Validate each character in the map
	if (!is_map_surrounded_by_walls(config)) // Ensure the map is surrounded by walls
		exit_with_error("Error: Map is not surrounded by walls", 1);
	if (!check_player_start(config)) // Ensure exactly one player start position exists
		exit_with_error("Error: Invalid or multiple player start positions", 1);
}
