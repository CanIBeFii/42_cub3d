/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:08:04 by fialexan          #+#    #+#             */
/*   Updated: 2023/09/05 12:37:01 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dda(t_game *mlx, t_map *map, t_player *player, t_map_info *info)
{
	int		index;
	double	camera_ray;
	t_ray	ray;

	index = 0;
	while (index < FOV)
	{
		ray.id = index;
		ray.map_pos.x = player->pos.x;
		ray.map_pos.y = player->pos.y;
		camera_ray = (2 * index) / (double) FOV - 1;
		ray.direction.x = player->direction.x + player->camera.x * camera_ray;
		ray.direction.y = player->direction.y + player->camera.y * camera_ray;
		ray.delta_dist.x = fabs(1 / ray.direction.x);
		ray.delta_dist.y = fabs(1 / ray.direction.y);
		dda_step_calc(&ray, player);
		dda_real_distance_calc(&ray, map);
		dda_wall_height(&ray);
		dda_side_selector(mlx, &ray, player, info);
		index++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->window, mlx->img.img, 0, 0);
}

void	dda_step_calc(t_ray *ray, t_player *player)
{
	if (ray->direction.x < 0)
	{
		ray->step.x = -1;
		ray->distance.x = (player->pos.x - ray->map_pos.x)
			* ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->distance.x = (ray->map_pos.x + 1.0 - player->pos.x)
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

	hit = 0;
	while (hit == 0)
	{
		if (ray->distance.x < ray->distance.y)
		{
			ray->distance.x += ray->delta_dist.x;
			ray->map_pos.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->distance.y += ray->delta_dist.y;
			ray->map_pos.y += ray->step.y;
			ray->side = 1;
		}
		if (map->map[ray->map_pos.y][ray->map_pos.x] == '1')
			hit = 1;
	}
	if (ray->side == 0)
		ray->real_distance = (ray->distance.x - ray->delta_dist.x);
	else
		ray->real_distance = (ray->distance.y - ray->delta_dist.y);
}

void	dda_wall_height(t_ray *ray)
{
	int	line_height;

	line_height = (int)(SCREEN_H / ray->real_distance);
	ray->wall_start = -line_height / 2 + SCREEN_H / 2;
	if (ray->wall_start < 0 || line_height < 0)
		ray->wall_start = 0;
	ray->wall_end = line_height / 2 + SCREEN_H / 2;
	if (ray->wall_end >= SCREEN_H || line_height < 0)
		ray->wall_end = SCREEN_H - 1;
}

void	dda_side_selector(t_game *mlx, t_ray *ray, t_player *player,
		t_map_info *info)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = player->pos.y + ray->real_distance * ray->direction.y;
	else
		wall_x = player->pos.x + ray->real_distance * ray->direction.x;
	wall_x -= floor(wall_x);
	ray->x_texture = (int)(wall_x * 64);
	if (ray->side == 0 && ray->direction.x > 0)
		ray->x_texture = 64 - ray->x_texture - 1;
	if (ray->side == 1 && ray->direction.y < 0)
		ray->x_texture = 64 - ray->x_texture - 1;
	if (ray->side == 0 && ray->direction.x > 0)
		draw_walls(mlx, ray, &info->ea_texture, ray->wall_end
			- ray->wall_start);
	else if (ray->side == 0 && ray->direction.x < 0)
		draw_walls(mlx, ray, &info->we_texture,
			ray->wall_end - ray->wall_start);
	else if (ray->side == 1 && ray->direction.y > 0)
		draw_walls(mlx, ray, &info->so_texture,
			ray->wall_end - ray->wall_start);
	else if (ray->side == 1 && ray->direction.y < 0)
		draw_walls(mlx, ray, &info->no_texture,
			ray->wall_end - ray->wall_start);
}
