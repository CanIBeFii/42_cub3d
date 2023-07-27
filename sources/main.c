/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:44:41 by fialexan          #+#    #+#             */
/*   Updated: 2023/07/27 17:00:28 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub3d(t_game *mlx)
{
	mlx_hook(mlx->window, 17, 0L, close_window, &mlx);
	mlx_hook(mlx->window, 2, 1L << 0, keys, &mlx);
	mlx_loop(mlx->mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_game	mlx;

	(void)argc;
	(void)argv;
	// check_file(argc, argv, &mlx);
	map_checker(argv[1]);
	create_window(&mlx);
	cub3d(&mlx);
	return (0);
}
