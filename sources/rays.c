/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:38:50 by mibernar          #+#    #+#             */
/*   Updated: 2023/05/24 12:57:30 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	get_distance(t_vector begin, t_vector end)
{
	float	distance;

	distance = sqrt(pow(end.x - begin.x, 2) + pow(end.y - begin.y, 2));
	return (distance);
}

t_vector	get_end_ray_cordinates(t_game *mlx, float loop, float x0, float y0)
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
	end.x = x;
	end.y = y;
	return (end);
}

void	draw_rays(t_game *mlx, float x0, float y0, float loop)
{
	t_vector	begin;
	t_vector	end;
	float		distance;
	int			ray_id;

	ray_id = 1;
	while (loop < PI / 6)
	{
		printf("%d\n", ray_id);
		begin.x = x0;
		begin.y = y0;
		end = get_end_ray_cordinates(mlx, loop, x0, y0);
		// bresenham_algo(begin, end, mlx);
		distance = get_distance(begin, end);
		draw_3d(mlx, distance, ray_id);
		loop += 0.017 / 2;
		ray_id++;
	}
}
