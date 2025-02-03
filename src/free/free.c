#include "../../include/cub3d.h"

// Function to free textures
void free_textures(t_textures *textures)
{
    // Free individual texture components if they are dynamically allocated
    free(textures->north);
    free(textures->east);
    free(textures->south);
    free(textures->west);
    free(textures->floor);
    free(textures->ceiling);
    free(textures->door);
    free(textures->gameover);
}

// Function to free the map
void free_map(t_map *map)
{
    // Free the grid array (rows of the map)
    for (int i = 0; i < map->height; i++)
    {
        free(map->grid[i]);
    }
    // Free the grid itself and then the map struct
    free(map->grid);
    free(map);
}


// Function to free config
void free_config(t_config *config)
{
    if (config == NULL)
        return;

    // Free the map, textures, and player if they were allocated
    free_map(config->map);        // Free the map structure
    free_textures(config->textures); // Free the texture structures
    free_player(config->player);  // Free the player structure

    // Finally, free the config structure itself
    free(config);
}

int	free_player(t_player *player)
{
	if (player)
	{
		if (player->dir)
			free(player->dir);
		if (player->plane)
			free(player->plane);
		if (player->pos)
			free(player->pos);
		free(player);
		return (0);
	}
	return (1);
}

