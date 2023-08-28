/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fialexan <fialexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:08:04 by fialexan          #+#    #+#             */
/*   Updated: 2023/08/28 17:47:12 by fialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dda(t_map *map, t_player *player)
{
	int		index;
	double	camera_ray;
	t_ray	ray;

	index = 0;
	ray.map_pos.x = player->pos.x;
	ray.map_pos.y = player->pos.y;
	while (index < FOV)
	{
		camera_ray = 2 * index / FOV - 1;
		ray.direction.x = player->direction.x + player->camera.x + camera_ray;
		ray.direction.y = player->direction.y + player->camera.y + camera_ray;
		ray.delta_dist.x = fabs(1 / ray.direction.x);
		ray.delta_dist.y = fabs(1 / ray.direction.y);
		dda_step_calc(&ray, player);
		dda_real_distance_calc(&ray, map);
		draw_wall()
		index++;
	}
}

void	dda_step_calc(t_ray *ray, t_player *player)
{
	if (ray->direction.x < 0)
	{
		ray->step.x = -1;
		ray->initial_distance.x = (player->pos.x - ray->map_pos.x)
			* ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->initial_distance.x = (ray->map_pos.x + 1.0 - player->pos.x)
			* ray->delta_dist.x;
	}
	if (ray->direction.y < 0)
	{
		ray->step.y = -1;
		ray->distance.y = (player->pos.y - ray->map_pos.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->distance.y = (ray->map_pos.y + 1.0 - player->pos.y)
			* ray->delta_dist.y;
	}
}

void	dda_real_distance_calc(t_ray *ray, t_map *map)
{
	int	hit;
	int	side;

	hit = 0;
	while (hit == 0)
	{
		if (ray->distance.x < ray->distance.y)
		{
			ray->distance.x += ray->delta_dist.x;
			ray->map_pos.x += ray->step.x;
			side = 0;
		}
		else
		{
			ray->distance.y += ray->delta_dist.y;
			ray->map_pos.y += ray->step.y;
			side = 1;
		}
		if (map->map[ray->map_pos.y][ray->map_pos.x] == '1')
			hit = 1;
	}
	if (side == 0)
		ray->real_distance = (ray->distance.x - ray->delta_dist.x);
	else
		ray->real_distance = (ray->distance.y - ray->delta_dist.y);
}
