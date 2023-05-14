/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:38:10 by mibernar          #+#    #+#             */
/*   Updated: 2023/05/14 12:53:02 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_img_clear(t_game *mlx)
{
	int	j;
	int	i;

	j = 0;
	while (j < (mlx->map_info.map_y * 64))
	{
		i = 0;
		while (i < (mlx->map_info.map_x * 64))
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
	*(unsigned int *)dst = color;
}

void	draw_rays(t_game *mlx, float x0, float y0, int color)
{
	float		x;
	float		y;
	int			i;
	t_vector	begin;
	t_vector	end;

	i = 1;
	x = (i * 64) * cos(mlx->player.pa) + x0;
	y = (i * 64) * sin(mlx->player.pa) + y0;
	while (mlx->map_layout[(int)y / 64][(int)x / 64] != '1')
	{
		i++;
		x = i * cos(mlx->player.pa) + x0;
		y = i * sin(mlx->player.pa) + y0;
		// printf("x: %f y: %f\n", x, y);
	}
	begin.x = x0;
	begin.y = y0;
	end.x = x;
	end.y = y;
	// printf("size: %d\n", mlx->map_info.map_x * 64);
	// printf("bx : %d by : %d\n", begin.x, begin.y);
	// printf("ex : %d ey : %d\n", end.x, end.y);
	(void)color;
	bresenham_algo(begin, end, mlx);
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

void	draw_line(t_game *mlx, float x2, float y2, int color)
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
			my_mlx_pixel_put(&mlx->img, x, y, color);
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
			my_mlx_pixel_put(&mlx->img, x, y, color);
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
			my_mlx_pixel_put(&mlx->img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}