/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:45:48 by mibernar          #+#    #+#             */
/*   Updated: 2023/06/13 19:18:28 by mibernar         ###   ########.fr       */
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

void	save_texture_array(t_game *mlx)
{
	int	fd;
	int	x;

	fd = open("./textures/south_wall.txt", O_RDONLY);
	if (fd < 0)
		return ;
	mlx->texture = malloc(sizeof(char *) * (NB_PIXLES_H + 1));
	if (!mlx->texture)
		return ;
	x = -1;
	while (++x <= 8)
		mlx->texture[x] = get_next_line(fd);
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
			my_mlx_pixel_put(&mlx->img, x, y, 0x00FF00);
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
