/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fialexan <fialexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:28:29 by mibernar          #+#    #+#             */
/*   Updated: 2023/08/07 15:48:54 by fialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

mbrarmbrnr1mbrnr1mbrarmbrnr1mbrnr1mbrarmbrnr1mbrnr#include "cub3d.h"

int	check_dup_textures(t_game *mlx, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (mlx->info.north_texture.img != NULL)
			return (1);
		mlx->info.north_texture.img = mlx_xpm_file_to_image(mlx->mlx_ptr, line,
			&mlx->info.north_texture.img_size.x, &mlx->info.north_texture.img_size.x);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (mlx->info.south_texture.img != NULL)
			return (1);
		mlx->info.south_texture.img = mlx_xpm_file_to_image(mlx->mlx_ptr, line,
			&mlx->info.south_texture.img_size.x, &mlx->info.south_texture.img_size.x);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	if (mlx->info.east_texture.img != NULL)
			return (1);
		mlx->info.east_texture.img = mlx_xpm_file_to_image(mlx->mlx_ptr, line,
			&mlx->info.east_texture.img_size.x, &mlx->info.east_texture.img_size.x);
	else
	{
		if (mlx->info.weast_texture.img != NULL)
			return (1);
		mlx->info.weast_texture.img = mlx_xpm_file_to_image(mlx->mlx_ptr, line,
			&mlx->info.weast_texture.img_size.x, &mlx->info.weast_texture.img_size.x);
	}
	return (0);
}

void	get_floor_rgb_values(t_game *mlx)
{
	mlx->info.floor_color.r = mlx->rgb.r;
	mlx->info.floor_color.g = mlx->rgb.g;
	mlx->info.floor_color.b = mlx->rgb.b;
}

void	get_ceiling_rgb_values(t_game *mlx)
{
	mlx->info.ceiling_color.r = mlx->rgb.r;
	mlx->info.ceiling_color.g = mlx->rgb.g;
	mlx->info.ceiling_color.b = mlx->rgb.b;
}

int	check_missing_info(t_map_info *info)
{
	if (info.east_texture.img == NULL || info.west_texture.img == NULL
			|| info.north_texture.img == NULL || info.south_texture.img == NULL
			|| info.ceiling_color.r == -1 || info.ceiling_color.g == -1
			|| info.ceiling_color.b == -1 || info.floor_color.r == -1
			|| info.floor_color.g == -1 || info.floor_color.b == -1)
		return (1);
	return (0);
}