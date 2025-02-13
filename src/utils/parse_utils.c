/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:01:20 by ekechedz          #+#    #+#             */
/*   Updated: 2025/02/13 15:40:37 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	validate_line(const char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' \
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& line[i] != ' ')
			error("Error: Invalid character in the map", 1);
		if (line[i] == '\n')
			error("New line in the map", 0);
		i++;
	}
}

void	process_map_line(t_config *config, const char *clean_line)
{
	char	**new_grid;
	int		line_length;
	size_t	old_size;
	size_t	new_size;

	old_size = sizeof(char *) * config->map->height;
	new_size = sizeof(char *) * (config->map->height + 1);
	new_grid = ft_realloc(config->map->grid, old_size, new_size);
	if (!new_grid)
		error("Failed to reallocate memory for map grid", 1);
	config->map->grid = new_grid;
	line_length = ft_strlen(clean_line);
	if (line_length > config->map->width)
		config->map->width = line_length;
	config->map->grid[config->map->height] = ft_strdup(clean_line);
	if (!config->map->grid[config->map->height])
		error("Failed to allocate memory for map line", 1);
	config->map->height++;
}

void	add_used_key(const char *key, char *used_keys[MAX_KEYS])
{
	int	i;

	i = 0;
	while (i < MAX_KEYS)
	{
		if (!used_keys[i])
		{
			used_keys[i] = ft_strdup(key);
			return ;
		}
		i++;
	}
}

int	key_already_used(const char *key, char *used_keys[MAX_KEYS])
{
	int	i;

	i = 0;
	while (i < MAX_KEYS)
	{
		if (used_keys[i] && strcmp(used_keys[i], key) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	*trim_trailing_spaces(const char *line)
{
	int	len;
	int	start;

	len = ft_strlen(line);
	start = 0;
	if (line[0] == '\n')
		error("Error: Line contains only whitespace or newline.", 1);
	while (len > 0 && (line[len - 1] == ' ' || line[len - 1] == '\n'))
		len--;
	if (start == len)
		return (ft_strdup(""));
	return (ft_substr(line, 0, len));
}
