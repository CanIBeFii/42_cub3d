/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:08:25 by mibernar          #+#    #+#             */
/*   Updated: 2023/05/23 17:04:18 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_img_clear(t_game *mlx, t_data data)
{
	int	j;
	int	i;

	j = 0;
	while (j < (mlx->map_info.map_y * 64))
	{
		i = 0;
		while (i < (mlx->map_info.map_x * 64))
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
