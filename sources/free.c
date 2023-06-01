/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fialexan <fialexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:41:52 by mibernar          #+#    #+#             */
/*   Updated: 2023/06/01 15:44:42 by fialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_double_array(char **double_array)
{
	int	i;

	i = 0;
	if (double_array == NULL)
		return ;
	while (double_array[i])
	{
		free(double_array[i]);
		i++;
	}
	free(double_array);
}

void	free_map_info(t_map_info *info)
{
	if (info->north_texture != NULL)
		free(info->north_texture);
	if (info->south_texture != NULL)
		free(info->south_texture);
	if (info->west_texture != NULL)
		free(info->west_texture);
	if (info->east_texture != NULL)
		free(info->east_texture);
	free(info);
}

void	free_map(t_map *map)
{
	free_map_info(map->info);
	free_double_array(map->map);
	free(map);
}
