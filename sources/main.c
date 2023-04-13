/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:28:11 by mibernar          #+#    #+#             */
/*   Updated: 2023/04/13 15:17:07 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_init(t_game *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->window = mlx_new_window(mlx->mlx_ptr, 1280, 720, "so_long");
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
	mlx_key_hook(mlx.window, keys, (void *)&mlx);
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
