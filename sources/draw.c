/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:38:10 by mibernar          #+#    #+#             */
/*   Updated: 2023/05/01 16:57:07 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_img_clear(t_game *mlx)
{
	size_t	j;
	size_t	i;

	j = 0;
	while (j < 800)
	{
		i = 0;
		while (i < 800)
		{
			my_mlx_pixel_put(&mlx->img, i, j, 0x000000);
			i++;
		}
		j++;
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

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

void	draw_line(t_game *mlx, float x2, float y2)
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
			my_mlx_pixel_put(&mlx->img, x + 7, y + 7, 0x00FF0000);
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
			my_mlx_pixel_put(&mlx->img, x + 7, y + 7, 0x00FF0000);
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
				my_mlx_pixel_put(&mlx->img, x + i, y + j, 0x4f4d4d);
			else if (i >= 60)
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

	i = 0;
	while (i < 15)
	{
		j = 0;
		while (j < 15)
		{
			my_mlx_pixel_put(&mlx->img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}