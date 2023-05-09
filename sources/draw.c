/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:38:10 by mibernar          #+#    #+#             */
/*   Updated: 2023/05/09 16:16:50 by mibernar         ###   ########.fr       */
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

void	draw_rays(t_player p, t_rays r, t_game mlx)
{
	t_vector	start;
	t_vector	end;
	float		a_tan;
	float		n_tan;

	r.ra = p.pa;
	r.r = 0;
	while (r.r < 1)
	{
		//horizontal
		r.dof = 0;
		a_tan = -1 / tan(r.ra);
		if (r.ra > PI)// looking up
		{
			r.ry = (((int)p.pos_y >> 6) << 6) - 0.0001;
			r.rx = (p.pos_y - r.ry) * a_tan + p.pos_x;
			r.yo = -64;
			r.xo = -r.yo * a_tan;
		}
		if (r.ra < PI)// looking down
		{
			r.ry = (((int)p.pos_y >> 6) << 6) + 64;
			r.rx = (p.pos_y - r.ry) * a_tan + p.pos_x;
			r.yo = 64;
			r.xo = -r.yo * a_tan;
		}
		if (r.ra == 0 || r.ra == PI)// looking straight left or right
		{
			r.rx = p.pos_x;
			r.ry = p.pos_y;
			r.dof = 8;
		}
		while (r.dof < 8)
		{
			r.mx = (int)(r.rx) >> 6;
			r.my = (int)(r.ry) >> 6;
			r.mp = r.my * mlx.map_info.map_x + r.mx;
			// printf("mpx*mpy: %d\np.posy:%d\nmp: %d\n", (mlx.map_info.map_x * mlx.map_info.map_y), (int)p.pos_y / 64, r.mp / 64);
			if (r.mp < (mlx.map_info.map_x * mlx.map_info.map_y) && mlx.map[((int)p.pos_y / 64)][(r.mp / 64)] == '1') //hit wall
				r.dof = 8;
			else //next line
			{
				r.rx += r.xo;
				r.ry += r.yo;
				r.dof += 1;
			}
		}
		//vertical
		r.dof = 0;
		n_tan = -tan(r.ra);
		if (r.ra > P2 && r.ra < P3)// looking left
		{
			r.rx = (((int)p.pos_x >> 6) << 6) - 0.0001;
			r.ry = (p.pos_x - r.rx) * n_tan + p.pos_y;
			r.xo = -64;
			r.yo = -r.xo * n_tan;
		}
		if (r.ra < P2 || r.ra > P3)// looking right
		{
			r.rx = (((int)p.pos_x >> 6) << 6) + 64;
			r.ry = (p.pos_x - r.rx) * n_tan + p.pos_y;
			r.xo = 64;
			r.yo = -r.xo * n_tan;
		}
		if (r.ra == 0 || r.ra == PI)// looking straight up or down
		{
			r.ry = p.pos_y;
			r.rx = p.pos_x;
			r.dof = 8;
		}
		while (r.dof < 8)
		{
			r.mx = (int)(r.rx) >> 6;
			r.my = (int)(r.ry) >> 6;
			r.mp = r.my * mlx.map_info.map_x + r.mx;
			// printf("mpx*mpy: %d\np.posy:%d\nmp: %d\n", (mlx.map_info.map_x * mlx.map_info.map_y), (int)p.pos_y / 64, r.mp / 64);
			if (r.mp < (mlx.map_info.map_x * mlx.map_info.map_y) && mlx.map[((int)p.pos_y / 64)][(r.mp / 64)] == '1') //hit wall
				r.dof = 8;
			else //next line
			{
				r.rx += r.xo;
				r.ry += r.yo;
				r.dof += 1;
			}
		}
		start.x = p.pos_x;
		start.y = p.pos_y;
		end.x = r.rx;
		end.y = r.ry;
		printf("x: %d\ny: %d\n", end.x, end.y);
		bresenham_algo(start, end, &mlx);
		// draw_line(&mlx, r.rx, r.ry, 0x00ff00);
		r.r++;
	}
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
	printf("player posx: %f\nplayer posy: %f\n", mlx->player.pos_x, mlx->player.pos_y);
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