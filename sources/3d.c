/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:45:48 by mibernar          #+#    #+#             */
/*   Updated: 2023/05/24 12:57:26 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling(t_game *mlx, float distance, int ray_id)
{
	int		x;
	int		y;

	y = 0;
	printf("distance: %f\n", distance);
	while (y < (SCREEN_H / 2))
	{
		x = (ray_id - 1) * 12;
		while (x < (ray_id * 12))
		{
			my_mlx_pixel_put(&mlx->img, x, y, 0x34B1EB);
			x++;
		}
		y++;
	}
}

void	draw_floor(t_game *mlx, float distance, int ray_id)
{
	int		x;
	int		y;

	(void)distance;
	y = (SCREEN_H / 2);
	while (y < SCREEN_H)
	{
		x = (ray_id - 1) * 12;
		while (x < (ray_id * 12))
		{
			my_mlx_pixel_put(&mlx->img, x, y, 0x7F7F7F);
			x++;
		}
		y++;
	}
}

void	draw_walls(t_game *mlx, float w_height, int ray_id)
{
	int		x;
	int		y;

	y = (SCREEN_H / 2) - (w_height / 2);
	while (y < (SCREEN_H / 2) - (w_height / 2) + w_height)
	{
		x = (ray_id - 1) * 12;
		while (x < (ray_id * 12))
		{
			my_mlx_pixel_put(&mlx->img, x, y, 0x00FF00);
			x++;
		}
		y++;
	}
}

void	draw_3d(t_game *mlx, float distance, int ray_id)
{
	float	w_height;

	w_height = (32 * SCREEN_H) / distance;
	draw_ceiling(mlx, distance, ray_id);
	draw_floor(mlx, distance, ray_id);
	draw_walls(mlx, w_height, ray_id);
}
