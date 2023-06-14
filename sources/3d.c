/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:45:48 by mibernar          #+#    #+#             */
/*   Updated: 2023/06/14 16:55:52 by mibernar         ###   ########.fr       */
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
	mlx->texture = malloc(sizeof(char *) * (NB_PIXELS_H + 1));
	if (!mlx->texture)
		return ;
	x = -1;
	while (++x <= 8)
		mlx->texture[x] = get_next_line(fd);
}

// void	draw_walls(t_game *mlx, float w_height, int ray_id)
// {
// 	int		x;
// 	int		y;

// 	y = (SCREEN_H / 2) - (w_height / 2);
// 	while (y < (SCREEN_H / 2) - (w_height / 2) + w_height)
// 	{
// 		x = (ray_id - 1) * (SCREEN_W / NB_RAYS);
// 		while (x < ray_id * (SCREEN_W / NB_RAYS))
// 		{
// 			my_mlx_pixel_put(&mlx->img, x, y, 0x00FF00);
// 			x++;
// 		}
// 		y++;
// 	}
// }

int	get_texture_x_coor(t_game *mlx)
{
	int	x;
	int	y;

	x = (int)mlx->ray.wall_hit_x;
	while (x > 64)
		x /= 64;
	y = (int)mlx->ray.wall_hit_y;
	while (y > 64)
		y /= 64;
	if ((x % 64) == 0)
	{
		x /= 8;
		return (x);
	}
	else
	{
		y /= 8;
		return (y);
	}
}

int	get_texture_y_coor(int y, float w_height)
{
	int	i;

	y = y - ((SCREEN_H / 2) - (w_height / 2));
	i = 0;
	while (i < y)
		i = i + (w_height / 8);
	return (i);
}

int	get_color(t_game *mlx, int y, float w_height)
{
	int	texture_x;
	int	texture_y;
	int	color;

	texture_x = get_texture_x_coor(mlx);
	texture_y = get_texture_y_coor(y, w_height);
	color = mlx->texture[texture_x][texture_y] - '0';
	return (color);
}

void	draw_walls(t_game *mlx, float w_height, int ray_id)
{
	int	color;
	int	x;
	int	y;

	y = (SCREEN_H / 2) - (w_height / 2);
	while (y < (SCREEN_H / 2) - (w_height / 2) + w_height)
	{
		color = get_color(mlx, y, w_height);
		x = (ray_id - 1) * (SCREEN_W / NB_RAYS);
		while (x < ray_id * (SCREEN_W / NB_RAYS))
		{
			my_mlx_pixel_put(&mlx->img, x, y, color);
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
