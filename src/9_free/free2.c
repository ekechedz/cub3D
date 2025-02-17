/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:17:10 by ekechedz          #+#    #+#             */
/*   Updated: 2025/02/17 14:17:13 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	*free_ray(t_ray *ray)
{
	if (ray)
	{
		free(ray->hit);
		free(ray);
	}
	return (NULL);
}

void	*free_game(t_game *game)
{
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
	free (game);
	return (NULL);
}

int	cleanup_all(t_game	*game, t_config *config)
{
	if (config)
		free_config(config);
	if (game)
		free_game(game);
	exit(1);
}

void	free_used_keys(char **used_keys)
{
	int	i;

	i = 0;
	if (!used_keys)
		return ;
	while (i < MAX_KEYS)
	{
		if (used_keys[i])
		{
			free(used_keys[i]);
			used_keys[i] = NULL;
		}
		i++;
	}
}

int	error(const char *message, int use_perror, t_game *g, t_config *c)
{
	if (use_perror && message)
		perror(message);
	else if (message)
		fprintf(stderr, "Error: %s\n", message);
	if (g || c)
		cleanup_all(g, c);
	exit(EXIT_FAILURE);
}
