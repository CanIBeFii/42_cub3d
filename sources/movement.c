/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:34:05 by mibernar          #+#    #+#             */
/*   Updated: 2023/04/17 18:12:05 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_dot(int key_code, t_game *mlx)
{
	// printf("key_code: %d\n", key_code);
	// printf("pdx: %f, pdy: %f\n", mlx->player.pdx, mlx->player.pdy);
	// printf("pa: %f\n", mlx->player.pa);
	if (key_code == 119) //W KEY
	{
		mlx->player.pos_x += mlx->player.pdx;
		mlx->player.pos_y += mlx->player.pdy;
	}
	else if (key_code == 97) //A KEY
	{
		mlx->player.pa -= 0.1;
		if (mlx->player.pa < 0)
			mlx->player.pa += (2 * PI);
		mlx->player.pdx = cos(mlx->player.pa) * 5;
		mlx->player.pdy = sin(mlx->player.pa) * 5;
	}
	else if (key_code == 115) //S KEY
	{
		mlx->player.pos_x -= mlx->player.pdx;
		mlx->player.pos_y -= mlx->player.pdy;
	}
	else if (key_code == 100) //D KEY
	{
		mlx->player.pa += 0.1;
		if (mlx->player.pa > 2 * PI)
			mlx->player.pa -= (2 * PI);
		mlx->player.pdx = cos(mlx->player.pa) * 5;
		mlx->player.pdy = sin(mlx->player.pa) * 5;
	}
	mlx_clear_window(mlx->mlx_ptr, mlx->window);
	draw_map(mlx);
	draw_player(mlx, mlx->player.pos_x, mlx->player.pos_y, 0x00FF0000);
	draw_line(mlx, mlx->player.pos_x + mlx->player.pdx * 10,
		mlx->player.pos_y + mlx->player.pdy * 10);
}
