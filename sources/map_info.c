/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:28:29 by mibernar          #+#    #+#             */
/*   Updated: 2023/08/16 16:23:04 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_texture(t_game *mlx, t_data *texture, char *line)
{
	texture->img = mlx_xpm_file_to_image(mlx->mlx_ptr, line,
			&texture->img_size.x, &texture->img_size.x);
}

int	check_dup_textures(t_game *mlx, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (mlx->info.no == 1)
			return (1);
		mlx->info.no = 1;
		get_texture(mlx, &mlx->info.no_texture, line);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (mlx->info.so == 1)
			return (1);
		mlx->info.so = 1;
		get_texture(mlx, &mlx->info.so_texture, line);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (mlx->info.ea == 1)
			return (1);
		mlx->info.ea = 1;
		get_texture(mlx, &mlx->info.ea_texture, line);
	}
	else
	{
		if (mlx->info.we == 1)
			return (1);
		mlx->info.we = 1;
		get_texture(mlx, &mlx->info.we_texture, line);
	}
	return (0);
}

void	get_rgb_values(t_rgb *surface, t_rgb color)
{
	surface->r = color.r;
	surface->g = color.g;
	surface->b = color.b;
}

int	check_missing_info(t_map_info *info)
{
	if (info->ea == -1 || info->we == -1 || info->no == -1 || info->so == -1
		|| info->ceiling_color.r == -1 || info->ceiling_color.g == -1
		|| info->ceiling_color.b == -1 || info->floor_color.r == -1
		|| info->floor_color.g == -1 || info->floor_color.b == -1)
		return (1);
	return (0);
}
