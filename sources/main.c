/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:28:11 by mibernar          #+#    #+#             */
/*   Updated: 2023/06/22 17:15:30 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_textures(t_game *mlx)
{
	mlx->texture.img = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/no.xpm",
			&mlx->texture_size.x, &mlx->texture_size.y);
}

void	game_init(t_game mlx)
{
	mlx.mlx_ptr = mlx_init();
	mlx.window = mlx_new_window(mlx.mlx_ptr, SCREEN_W, SCREEN_H, "cub3d");
	mlx.img.img = mlx_new_image(mlx.mlx_ptr, SCREEN_W, SCREEN_H);
	mlx.img.addr = mlx_get_data_addr(mlx.img.img, &mlx.img.bits_per_pixel,
			&mlx.img.line_length, &mlx.img.endian);

	open_textures(&mlx);
	// draw_map(&mlx);
	// draw_player(&mlx, mlx.player.pos_x, mlx.player.pos_y, 0x00FF0000);
	// draw_line(&mlx, mlx.player.pos_x, mlx.player.pos_y, 0x00FF0000);
	draw_rays(&mlx, mlx.player.pos_x, mlx.player.pos_y, -(PI / 6));
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.window, mlx.img.img, 0, 0);
	mlx_hook(mlx.window, 17, 0L, close_window, &mlx);
	mlx_hook(mlx.window, 2, 1L << 0, keys, &mlx);
	mlx_loop(mlx.mlx_ptr);
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
	mlx->player.pa = 0;
	mlx->player.pdx = cos(mlx->player.pa) * 5;
	mlx->player.pdy = sin(mlx->player.pa) * 5;
	mlx->map_info.map_x = 0;
	mlx->map_info.map_y = 0;
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
	game_init(mlx);
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
