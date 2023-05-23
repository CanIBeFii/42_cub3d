/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:45:48 by mibernar          #+#    #+#             */
/*   Updated: 2023/05/23 17:12:43 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling(t_game *mlx, float distance, int ray_id)
{
	int		x;
	int		y;

	y = 0;
	while (y < (SCREEN_H / 2) - (distance / 2))
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

	y = (SCREEN_H / 2) + (distance / 2);
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

void	draw_walls(t_game *mlx, float distance, int ray_id)
{
	int		x;
	int		y;

	y = (SCREEN_H / 2) - (distance / 2);
	while (y < (ray_id * 12))
	{
		x = (ray_id - 1) * 12;
		while (x < SCREEN_H)
		{
			my_mlx_pixel_put(&mlx->img, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

void	draw_3d(t_game *mlx, float distance, int ray_id)
{
	draw_ceiling(mlx, distance, ray_id);
	draw_floor(mlx, distance, ray_id);
	draw_walls(mlx, distance, ray_id);
}
