/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:34:05 by mibernar          #+#    #+#             */
/*   Updated: 2023/05/31 18:43:54 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	direction_keys(int key_code, t_game *mlx)
{
	if (key_code == L_ARROW)
	{
		mlx->player.pa -= 0.05;
		if (mlx->player.pa < 0)
			mlx->player.pa += (2 * PI);
		mlx->player.pdx = cos(mlx->player.pa) * 5;
		mlx->player.pdy = sin(mlx->player.pa) * 5;
	}
	else if (key_code == R_ARROW)
	{
		mlx->player.pa += 0.05;
		if (mlx->player.pa > (2 * PI))
			mlx->player.pa -= (2 * PI);
		mlx->player.pdx = cos(mlx->player.pa) * 5;
		mlx->player.pdy = sin(mlx->player.pa) * 5;
	}
}

void	movement_keys(int key_code, t_game *mlx)
{
	if (key_code == W_KEY)
	{
		mlx->player.pos_x += mlx->player.pdx;
		mlx->player.pos_y += mlx->player.pdy;
	}
	else if (key_code == A_KEY)
	{
		mlx->player.pos_x += cos(mlx->player.pa - (PI / 2)) * 5;
		mlx->player.pos_y += sin(mlx->player.pa - (PI / 2)) * 5;
	}
	else if (key_code == S_KEY)
	{
		mlx->player.pos_x -= mlx->player.pdx;
		mlx->player.pos_y -= mlx->player.pdy;
	}
	else if (key_code == D_KEY)
	{
		mlx->player.pos_x += cos(mlx->player.pa + (PI / 2)) * 5;
		mlx->player.pos_y += sin(mlx->player.pa + (PI / 2)) * 5;
	}
}

void	move_dot(int key_code, t_game *mlx)
{
	movement_keys(key_code, mlx);
	direction_keys(key_code, mlx);
	my_img_clear(mlx, mlx->img);
	// draw_map(mlx);
	// draw_player(mlx, mlx->player.pos_x, mlx->player.pos_y, 0x00FF0000);
	// draw_line(mlx, mlx->player.pos_x, mlx->player.pos_y, 0x00FF0000);
	draw_rays(mlx, mlx->player.pos_x, mlx->player.pos_y, -(PI / 6));
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->window, mlx->img.img, 0, 0);
}
