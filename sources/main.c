/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:44:41 by fialexan          #+#    #+#             */
/*   Updated: 2023/07/26 15:33:13 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_window(t_game *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->window = mlx_new_window(mlx->mlx_ptr, SCREEN_W, SCREEN_H, "cub3d");
	mlx->img.img = mlx_new_image(mlx->mlx_ptr, SCREEN_W, SCREEN_H);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel,
			&mlx->img.line_length, &mlx->img.endian);
}

int	main(int argc, char **argv)
{
	t_game	mlx;

	check_file(argc, argv, &mlx);
	map_checker(argv[1]);
	create_window(&mlx);
	return (0);
}
