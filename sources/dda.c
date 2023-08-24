/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fialexan <fialexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:08:04 by fialexan          #+#    #+#             */
/*   Updated: 2023/08/24 16:43:31 by fialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dda(t_map *map, t_player *player)
{
	int		index;
	double	camera_ray;
	t_ray	ray;

	index = 0;
	ray.map_pos.x = player->pos.x;
	ray.map_pos.y = player->pos.y;
	while (index < FOV)
	{
		camera_ray = 2 * index / FOV - 1;
		ray.direction.x = player->direction.x + player->camera.x + camera_ray;
		ray.direction.y = player->direction.y + player->camera.y + camera_ray;
		ray.delta_dist.x = fabs(1 / ray.direction.x);
		ray.delta_dist.y = fabs(1 / ray.direction.y);
		
		index++;
	}
}
