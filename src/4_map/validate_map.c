/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:34:22 by ekechedz          #+#    #+#             */
/*   Updated: 2025/02/17 14:16:18 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (nx < 0 || nx >= map->height || ny < 0 \
			|| ny >= (int)ft_strlen(map->grid[nx]) || map->grid[nx][ny] == ' ')
			return (1);
		d++;
	}
	return (0);
}

void	validate_open_spaces(t_map *map, t_config *config)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j] == '0' && is_open_to_space(map, i, j))
				error("Walkable area next to open space!", 0, NULL, config);
			j++;
		}
		i++;
	}
}

void	initialize_player(t_map *map, t_config *config)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			if (map->grid[i][j] && ft_strchr("NSEW", map->grid[i][j]))
			{
				if (count == 1)
					error("You need to one player", 0, NULL, config);
				count ++;
				config->player = init_player(i, j);
				if (!init_pos_dir_plane(config->player, map->grid[i][j]))
					error("Failure initializing vectors", 0, NULL, config);
				map->grid[i][j] = '0';
			}
		}
	}
	if (count != 1)
		error("You need at least one player", 0, NULL, config);
}

void	validate_map(t_map *map, t_config *config)
{
	initialize_player(map, config);
	validate_open_spaces(map, config);
	if (!all_keys_used(config->used_keys))
		error("Not all keys are used in the map", 0, NULL, config);
}

void	handle_color_line(t_config *config, char *line, \
	char *key, int *color_field)
{
	if (key_already_used(key, config->used_keys))
	{
		free(line);
		error("Error: Duplicate color", 1, NULL, config);
	}
	if (!parse_color(line + 2, color_field))
	{
		free(line);
		error("Error: Couldn't parse color", 1, NULL, config);
	}
	add_used_key(key, config->used_keys);
}
