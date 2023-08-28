/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:28:29 by mibernar          #+#    #+#             */
/*   Updated: 2023/08/28 16:28:13 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_dup_textures(t_game *mlx, char *line, char *path)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (mlx->info.no != NULL)
			return (1);
		mlx->info.no = ft_strdup(path);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (mlx->info.so != NULL)
			return (1);
		mlx->info.so = ft_strdup(path);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (mlx->info.ea != NULL)
			return (1);
		mlx->info.ea = ft_strdup(path);
	}
	else
	{
		if (mlx->info.we != NULL)
			return (1);
		mlx->info.we = ft_strdup(path);
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
	if (info->ea == NULL || info->we == NULL || info->no == NULL
		|| info->so == NULL || info->ceiling_color.r == -1
		|| info->ceiling_color.g == -1 || info->ceiling_color.b == -1
		|| info->floor_color.r == -1 || info->floor_color.g == -1
		|| info->floor_color.b == -1)
		return (1);
	return (0);
}
