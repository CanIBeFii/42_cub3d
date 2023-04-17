/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:38:10 by mibernar          #+#    #+#             */
/*   Updated: 2023/04/17 18:23:08 by mibernar         ###   ########.fr       */
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
				draw_square(mlx, x * 64, (i - start - 1) * 64, 0x00FFFFFF);
			else
				draw_square(mlx, x * 64, (i - start - 1) * 64, 0x00000000);
			x++;
		}
		i++;
	}
}

void	draw_line(t_game *mlx, int x2, int y2)
{
	int		dx;
	int		dy;
	int		i;
	int		x;
	int		y;

	dx = x2 - mlx->player.pos_x;
	dy = y2 - mlx->player.pos_y;
	if (dx >= 0)
	{
		i = 1;
		while (i <= dx)
		{
			x = mlx->player.pos_x + (i * dx) / dx;
			y = mlx->player.pos_y + (i * dy) / dx;
			mlx_pixel_put(mlx->mlx_ptr, mlx->window, x + 7, y + 7, 0x00FF0000);
			i++;
		}
	}
	else
	{
		i = 1;
		while (i <= -dx)
		{
			x = mlx->player.pos_x - (i * dx) / dx;
			y = mlx->player.pos_y - (i * dy) / dx;
			mlx_pixel_put(mlx->mlx_ptr, mlx->window, x + 7, y + 7, 0x00FF0000);
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
			if (j >= 60)
				mlx_pixel_put(mlx->mlx_ptr, mlx->window, x + i, y + j, 0x4f4d4d);
			else if (i >= 60)
				mlx_pixel_put(mlx->mlx_ptr, mlx->window, x + i, y + j, 0x4f4d4d);
			else
				mlx_pixel_put(mlx->mlx_ptr, mlx->window, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_game *mlx, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 15)
	{
		j = 0;
		while (j < 15)
		{
			mlx_pixel_put(mlx->mlx_ptr, mlx->window, x + i, y + j, color);
			j++;
		}
		i++;
	}
}