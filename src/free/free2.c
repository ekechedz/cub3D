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

void	free_used_keys(char *used_keys[MAX_KEYS])
{
	int	i;

	i = 0;
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
