#include "../../include/cub3d.h"

int	is_open_to_space(t_map *map, int x, int y)
{
	int	directions[4][2];
	int	nx;
	int	ny;
	int	d;

	directions[0][0] = 1;
	directions[0][1] = 0;
	directions[1][0] = -1;
	directions[1][1] = 0;
	directions[2][0] = 0;
	directions[2][1] = 1;
	directions[3][0] = 0;
	directions[3][1] = -1;
	d = 0;
	while (d < 4)
	{
		nx = x + directions[d][0];
		ny = y + directions[d][1];
		if (nx >= 0 && nx < map->height && ny >= 0 && ny < map->width && map->grid[nx][ny] == ' ')
			return (1);
		d++;
	}
	return (0);
}


void print_map(char **grid, int height)
{
	for (int i = 0; i < height; i++)
		printf("[%d]: %s\n", i, grid[i]);
}

void validate_map(t_map *map)
{
	print_map(map->grid, map->height);
	int i;
	int j;

	i = 0 ;

	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j] == '0' && is_open_to_space(map, i, j))
				exit_with_error("Walkable area next to open space!", 0);
			j++;
		}
		i++;
	}
}
