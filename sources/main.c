/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fialexan <fialexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:44:41 by fialexan          #+#    #+#             */
/*   Updated: 2023/08/07 15:47:02 by fialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub3d(t_game *mlx)
{
	mlx_hook(mlx->window, 17, 0L, close_window, &mlx);
	mlx_hook(mlx->window, 2, 1L << 0, keys, &mlx);
	mlx_loop(mlx->mlx_ptr);
}

void	init_vars(t_game *mlx)
{
	mlx->info.east_texture.img = NULL;
	mlx->info.west_texture.img = NULL;
	mlx->info.north_texture.img = NULL;
	mlx->info.south_texture.img = NULL;
	mlx->info.ceiling_color.r = -1;
	mlx->info.ceiling_color.g = -1;
	mlx->info.ceiling_color.b = -1;
	mlx->info.floor_color.r = -1;
	mlx->info.floor_color.g = -1;
	mlx->info.floor_color.b = -1;
}

int	main(int argc, char **argv)
{
	t_game	mlx;

	(void)argc;
	(void)argv;
	// check_file(argc, argv, &mlx);
	init_vars(&mlx);
	map_checker(argv[1], &mlx);
	create_window(&mlx);
	cub3d(&mlx);
	return (0);
}
