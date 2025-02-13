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
