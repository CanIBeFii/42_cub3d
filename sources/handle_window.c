/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fialexan <fialexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:36:57 by mibernar          #+#    #+#             */
/*   Updated: 2023/08/08 13:59:36 by fialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_window(t_game *mlx)
{
	mlx->window = mlx_new_window(mlx->mlx_ptr, SCREEN_W, SCREEN_H, "cub3d");
	mlx->img.img = mlx_new_image(mlx->mlx_ptr, SCREEN_W, SCREEN_H);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel,
			&mlx->img.line_length, &mlx->img.endian);
}

int	close_window(t_game *mlx)
{
	(void)mlx;
	exit (EXIT_FAILURE);
	return (0);
}
