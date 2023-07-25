/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fialexan <fialexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:45:48 by mibernar          #+#    #+#             */
/*   Updated: 2023/07/25 14:35:30 by fialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../old_includes/cub3d.h"

void	draw_ceiling(t_game *mlx)
{
	int		x;
	int		y;

	y = 0;
	while (y < (SCREEN_H / 2))
	{
		x = 0;
		while (x < SCREEN_W)
		{
			my_mlx_pixel_put(&mlx->img, x, y, 0x34B1EB);
			x++;
		}
		y++;
	}
}

void	draw_floor(t_game *mlx)
{
	int		x;
	int		y;

	y = (SCREEN_H / 2);
	while (y < SCREEN_H)
	{
		x = 0;
		while (x < SCREEN_W)
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
	int		tex_x;
	int		tex_y;

	y = (SCREEN_H / 2) - (w_height / 2);
	tex_x = (int)w_height * 64;
	while (y <= (SCREEN_H / 2) - (w_height / 2) && y <= SCREEN_H)
	{
		tex_y = (y - (SCREEN_H / 2) - (w_height / 2) * 64);
		x = (ray_id - 1) * (SCREEN_W / NB_RAYS);
		while (x < ray_id * (SCREEN_W / NB_RAYS))
		{
			my_mlx_pixel_put(&mlx->img, x, y, get_color());
			x++;
		}
		y++;
	}
}

void	draw_3d(t_game *mlx, float distance, int ray_id, float ray_angle)
{
	float	w_height;

	distance = distance * cos(ray_angle);
	w_height = (64 * SCREEN_H) / distance;
	if (w_height > SCREEN_H)
		w_height = SCREEN_H;
	draw_walls(mlx, w_height, ray_id);
}
