/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fialexan <fialexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:44:18 by fialexan          #+#    #+#             */
/*   Updated: 2023/09/06 14:23:06 by fialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	save_player_pos(t_player *player, int spawn_y, int spawn_x, char spawn_dir)
{
	player->pos.x = spawn_x + 0.5;
	player->pos.y = spawn_y + 0.5;
	if (spawn_dir == 'N')
	{
		player->direction.y = -1;
		player->camera.x = 0.6;
	}
	else if (spawn_dir == 'E')
	{
		player->direction.x = 1;
		player->camera.y = 0.6;
	}
	else if (spawn_dir == 'S')
	{
		player->direction.y = 1;
		player->camera.x = -0.6;
	}
	else
	{
		player->direction.x = -1;
		player->camera.y = -0.6;
	}
	return (1);
}
