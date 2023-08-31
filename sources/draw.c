/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:14:53 by mibernar          #+#    #+#             */
/*   Updated: 2023/08/31 14:19:58 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_img_clear(t_data data)
{
	int	j;
	int	i;

	j = 0;
	while (j < SCREEN_H)
	{
		i = 0;
		while (i < SCREEN_W)
		{
			my_mlx_pixel_put(&data, i, j, 0x000000);
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

int	get_color(int tex_x, int tex_y, t_data *curr)
{
	int		bpp;
	char	*data;
	int		color;
	int		pixel_index;
	int		i;

	data = mlx_get_data_addr(curr->img, &curr->bits_per_pixel,
			&curr->line_length, &curr->endian);
	bpp = curr->bits_per_pixel / 8;
	color = 0;
	pixel_index = tex_y * 64 + tex_x;
	i = -1;
	while (++i < bpp)
		color |= data[(pixel_index * bpp) + i] << (8 * i);
	return (color);
}

void	draw_walls(t_game *mlx, t_ray *ray, t_data *texture, double wall_height)
{
	double	step;
	double	texture_pos;
	int		color;
	int		y;

	step = texture->img_size.y / wall_height;
	texture_pos = (ray->wall_start - SCREEN_H / 2 + wall_height / 2) * step;
	y = ray->wall_start;
	while (y < ray->wall_end)
	{
		color = get_color(ray->x_texture, texture_pos, texture);
		my_mlx_pixel_put(&mlx->img, ray->id, y, color);
		texture_pos += step;
		y++;
	}
	draw_floor_ceiling(mlx, ray);
}

void	draw_floor_ceiling(t_game *mlx, t_ray *ray)
{
	int	c_color;
	int	f_color;
	int	y;

	c_color = create_rgb(&mlx->info.ceiling_color);
	f_color = create_rgb(&mlx->info.floor_color);
	y = 0;
	while (y < ray->wall_start)
	{
		my_mlx_pixel_put(&mlx->img, ray->id, y, c_color);
		y++;
	}
	y = ray->wall_end + 1;
	while (y < SCREEN_H)
	{
		my_mlx_pixel_put(&mlx->img, ray->id, y, f_color);
		y++;
	}
}
