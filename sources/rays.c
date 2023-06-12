/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:38:50 by mibernar          #+#    #+#             */
/*   Updated: 2023/06/12 16:18:46 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	get_distance(t_vector begin, t_vector end)
{
	float	distance;

	distance = sqrt(pow(end.x - begin.x, 2) + pow(end.y - begin.y, 2));
	return (distance);
}

void	get_end_ray_cordinates(t_game *mlx, float loop, float x0, float y0)
{
	t_vector	end;
	float		x;
	float		y;
	int			i;

	i = 1;
	x = i * cos(mlx->player.pa + loop) + x0;
	y = i * sin(mlx->player.pa + loop) + y0;
	while (mlx->map_layout[(int)y / 64][(int)x / 64] != '1')
	{
		i++;
		x = i * cos(mlx->player.pa + loop) + x0;
		y = i * sin(mlx->player.pa + loop) + y0;
	}
	mlx->ray->wall_hit_x = x;
	mlx->ray->wall_hit_y = y;
}

void	draw_rays(t_game *mlx, float x0, float y0, float loop)
{
	t_vector	begin;
	t_vector	end;
	float		distance;
	int			ray_id;

	ray_id = 1;
	draw_floor(mlx);
	draw_ceiling(mlx);
	while (loop < PI / 6)
	{
		mlx->ray->ray_angle = loop;
		begin.x = x0;
		begin.y = y0;
		get_end_ray_cordinates(mlx, loop, x0, y0);
		// bresenham_algo(begin, end, mlx);
		mlx->ray->distance = get_distance(begin, end) * 1.2;
		draw_3d(mlx, ray_id);
		loop += (FOV / NB_RAYS);
		// printf("%d\n loop: %f\n", ray_id, loop);
		ray_id++;
	}
}
