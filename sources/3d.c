/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:45:48 by mibernar          #+#    #+#             */
/*   Updated: 2023/06/22 17:15:08 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	get_color(int tex_x, int tex_y, int i, t_data *curr)
{
	int			bpp;
	char		*data;
	int			color;
	int			pixel_index;

	data = mlx_get_data_addr(curr->img, &curr->bits_per_pixel,
			&curr->line_length, &curr->endian);
	bpp = curr->bits_per_pixel;
	bpp /= 8;
	color = 0;
	pixel_index = tex_y * 64 + tex_x;
	i = -1;
	while (++i < bpp)
		color |= data[(pixel_index * bpp) + i] << (8 * i);
	return (color);
}

void	draw_walls(t_game *mlx, float w_height, int ray_id)
{
	int		x;
	int		y;

	y = (SCREEN_H / 2) - (w_height / 2);
	while (y < (SCREEN_H / 2) - (w_height / 2) + w_height)
	{
		x = (ray_id - 1) * (SCREEN_W / NB_RAYS);
		while (x < ray_id * (SCREEN_W / NB_RAYS))
		{
			my_mlx_pixel_put(&mlx->img, x, y, get_color(mlx->texture_size.x *
						((float)x - ((ray_id - 1) * (SCREEN_W / NB_RAYS))) / ((float)ray_id * (SCREEN_W / NB_RAYS) - ((ray_id - 1) * (SCREEN_W / NB_RAYS))),
						mlx->texture_size.y * ((float)y - ((SCREEN_H / 2) - (w_height / 2))) / (((SCREEN_H / 2) - (w_height / 2)) + w_height - ((SCREEN_H / 2) - (w_height / 2))), 0,
						&mlx->texture));
			x++;
		}
		y++;
	}
}

void	draw_3d(t_game *mlx, int ray_id)
{
	float	w_height;

	// printf("here %f\n", mlx->ray.distance);
	mlx->ray.distance = mlx->ray.distance * cos(mlx->ray.ray_angle);
	w_height = (64 * SCREEN_H) / mlx->ray.distance;
	if (w_height > SCREEN_H)
		w_height = SCREEN_H;
	draw_walls(mlx, w_height, ray_id);
}
