/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:27:28 by ekechedz          #+#    #+#             */
/*   Updated: 2025/02/13 18:08:40 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_empty_or_map_started(const char *line, int map_started)
{
	if (map_started == 0)
	{
		if (*line == '\0' || *line == '\n')
			return (1);
	}
	else
	{
		if (*line == '\0')
			return (1);
	}
	return (0);
}

void	parse_color_line(t_config *config, const char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (key_already_used("F", config->used_keys))
			error("Error: Duplicate 'F' floor color", 1);
		parse_color(line + 2, config->floor_color);
		add_used_key("F", config->used_keys);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (key_already_used("C", config->used_keys))
			error("Error: Duplicate 'C' ceiling color", 1);
		parse_color(line + 2, config->ceiling_color);
		add_used_key("C", config->used_keys);
	}
}

void	parse_north_south_texture(t_config *config, const char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (key_already_used("NO", config->used_keys))
			error("Error: Duplicate 'NO' texture", 1);
		config->textures->north->img_ptr = ft_strdup(line + 3);
		add_used_key("NO", config->used_keys);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (key_already_used("SO", config->used_keys))
			error("Error: Duplicate 'SO' texture", 1);
		config->textures->south->img_ptr = ft_strdup(line + 3);
		add_used_key("SO", config->used_keys);
	}
}

void	parse_west_east_texture(t_config *config, const char *line)
{
	if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (key_already_used("WE", config->used_keys))
			error("Error: Duplicate 'WE' texture", 1);
		config->textures->west->img_ptr = ft_strdup(line + 3);
		add_used_key("WE", config->used_keys);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (key_already_used("EA", config->used_keys))
			error("Error: Duplicate 'EA' texture", 1);
		config->textures->east->img_ptr = ft_strdup(line + 3);
		add_used_key("EA", config->used_keys);
	}
}

void	parse_texture_line(t_config *config, const char *line)
{
	parse_north_south_texture(config, line);
	parse_west_east_texture(config, line);
}
