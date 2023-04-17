/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:28:11 by mibernar          #+#    #+#             */
/*   Updated: 2023/04/17 18:16:24 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_init(t_game *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->window = mlx_new_window(mlx->mlx_ptr, 1720, 1080, "so_long");
	draw_map(mlx);
	draw_player(mlx, mlx->player.pos_x, mlx->player.pos_y, 0x00FF0000);
	draw_line(mlx, mlx->player.pos_x + mlx->player.pdx * 10,
		mlx->player.pos_y + mlx->player.pdy * 10);
	mlx_hook(mlx->window, 17, 0L, close_window, &mlx);
}

void	init_vars(t_game *mlx)
{
	mlx->map_info.north = 0;
	mlx->map_info.south = 0;
	mlx->map_info.west = 0;
	mlx->map_info.east = 0;
	mlx->map_info.ceiling = 0;
	mlx->map_info.floor = 0;
	mlx->map = NULL;
	mlx->player.pos_x = 0;
	mlx->player.pos_y = 0;
	mlx->player.pdx = cos(mlx->player.pa) * 5;
	mlx->player.pdy = sin(mlx->player.pa) * 5;
}

void	cub3d(int fd, char *path)
{
	t_game	mlx;

	init_vars(&mlx);
	if (map_check(fd, path, &mlx) == 0)
	{
		free_double_array(mlx.map);
		perror("ERROR: invalid map");
		return ;
	}
	game_init(&mlx);
	mlx_hook(mlx.window, 2, 1L << 0, keys, &mlx);
	mlx_loop(mlx.mlx_ptr);
}

int	main(int argc, char **argv)
{
	char	*path;
	int		fd;
	int		x;

	if (argc != 2)
	{
		perror("ERROR: invalid number of arguments");
		return (1);
	}
	path = argv[1];
	x = ft_strlen(path) - 1;
	if (path[x] != 'b' || path[x - 1] != 'u' || path[x - 2] != 'c'
		|| path[x - 3] != '.')
	{
		perror("ERROR: invalid file type");
		return (1);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("ERROR: can't open file");
		return (1);
	}
	cub3d(fd, path);
	return (0);
}
