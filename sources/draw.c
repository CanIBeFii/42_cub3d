/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:38:10 by mibernar          #+#    #+#             */
/*   Updated: 2023/05/23 17:29:23 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map(t_game *mlx)
{
	int	x;
	int	i;
	int	start;

	start = mlx->map_info.last_line_info_elem;
	i = start;
	while (mlx->map[i])
	{
		x = 0;
		while (mlx->map[i][x] && mlx->map[i][x] != '\n')
		{
			if (mlx->map[i][x] == '1')
				draw_square(mlx, (x * 64) + SCREEN_W, (i - start - 1) * 64, 0x00FFFFFF);
			else
				draw_square(mlx, (x * 64) + SCREEN_W, (i - start - 1) * 64, 0x00000000);
			x++;
		}
		i++;
	}
}

void	draw_line(t_game *mlx, float x2, float y2, int color)
{
	int		dx;
	int		dy;
	int		i;

	dx = x2 - mlx->player.pos_x;
	dy = y2 - mlx->player.pos_y;
	i = 1;
	if (dx >= 0)
	{
		while (i <= dx)
		{
			my_mlx_pixel_put(&mlx->img, (mlx->player.pos_x + (i * dx) / dx),
				mlx->player.pos_y + (i * dy) / dx, color);
			i++;
		}
	}
	else
	{
		while (i <= -dx)
		{
			my_mlx_pixel_put(&mlx->img, mlx->player.pos_x - (i * dx) / dx,
				mlx->player.pos_y - (i * dy) / dx, color);
			i++;
		}
	}
}

void	draw_square(t_game *mlx, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 65)
	{
		j = 0;
		while (j < 65)
		{
			if (j >= 63)
				my_mlx_pixel_put(&mlx->img, x + i, y + j, 0x4f4d4d);
			else if (i >= 63)
				my_mlx_pixel_put(&mlx->img, x + i, y + j, 0x4f4d4d);
			else
				my_mlx_pixel_put(&mlx->img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_game *mlx, int x, int y, int color)
{
	int	i;
	int	j;

	i = -7;
	printf("x: %d y: %d\n", x, y);
	while (i < 8)
	{
		j = -7;
		while (j < 8)
		{
			my_mlx_pixel_put(&mlx->img, (x + i) + SCREEN_W, y + j, color);
			j++;
		}
		i++;
	}
}
