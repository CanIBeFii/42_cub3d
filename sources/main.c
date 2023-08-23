/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:44:41 by fialexan          #+#    #+#             */
/*   Updated: 2023/08/23 17:21:46 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub3d(t_game *mlx)
{
	mlx->mlx_ptr = mlx_init();
	create_window(mlx);
	open_imgs(mlx, &mlx->info);
	draw_rays(mlx);
	mlx_hook(mlx->window, 17, 0L, close_window, mlx);
	mlx_hook(mlx->window, 2, 1L << 0, keys, mlx);
	mlx_loop(mlx->mlx_ptr);
}

void	init_vars(t_game *mlx)
{
	mlx->info.ea = NULL;
	mlx->info.we = NULL;
	mlx->info.no = NULL;
	mlx->info.so = NULL;
	mlx->info.ceiling_color.r = -1;
	mlx->info.ceiling_color.g = -1;
	mlx->info.ceiling_color.b = -1;
	mlx->info.floor_color.r = -1;
	mlx->info.floor_color.g = -1;
	mlx->info.floor_color.b = -1;
	mlx->map.map = NULL;
}

int	main(int argc, char **argv)
{
	t_game	mlx;

	check_file(argc, argv, &mlx);
	init_vars(&mlx);
	map_checker(argv[1], &mlx);
	cub3d(&mlx);
	return (0);
}
