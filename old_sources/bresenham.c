/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:26:43 by mibernar          #+#    #+#             */
/*   Updated: 2023/05/19 16:01:29 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bresenham_algo(t_vector begin, t_vector end, t_game *mlx)
{
	t_bresenham	algo;

	algo = bresenham_init(begin, end);
	if (begin.x > (mlx->map_info.map_x * 64) || begin.x < 0
		|| begin.y > (mlx->map_info.map_y * 64) || begin.y < 0)
		return ;
	bresenham_loop(begin, end, mlx, algo);
	if (begin.x < (mlx->map_info.map_x * 64) && begin.x > 0
		&& begin.y < (mlx->map_info.map_y * 64) && begin.y > 0)
		my_mlx_pixel_put(&mlx->img, begin.x, begin.y, 0x00F0ABD7);
}

void	bresenham_loop(t_vector begin, t_vector end, t_game *mlx,
	t_bresenham algo)
{
	while (begin.x != end.x || begin.y != end.y)
	{
		my_mlx_pixel_put(&mlx->img, begin.x, begin.y, 0x00FF00);
		algo.abs_diff2x = algo.abs_diff * 2;
		if (algo.abs_diff2x > -algo.absolute_y)
		{
			algo.abs_diff -= algo.absolute_y;
			begin.x += algo.x_modifier;
		}
		if (algo.abs_diff2x < algo.absolute_x)
		{
			algo.abs_diff += algo.absolute_x;
			begin.y += algo.y_modifier;
		}
		if (begin.x > (mlx->map_info.map_x * 64) || begin.x < 0
			|| begin.y > (mlx->map_info.map_y * 64) || begin.y < 0)
			break ;
	}
}

t_bresenham	bresenham_init(t_vector begin, t_vector end)
{
	t_bresenham	algo;

	algo.absolute_x = (int)fabs((double)end.x - (double)begin.x);
	algo.absolute_y = (int)fabs((double)end.y - (double)begin.y);
	if (begin.x < end.x)
		algo.x_modifier = 1;
	else
		algo.x_modifier = -1;
	if (begin.y < end.y)
		algo.y_modifier = 1;
	else
		algo.y_modifier = -1;
	algo.abs_diff = algo.absolute_x - algo.absolute_y;
	return (algo);
}
