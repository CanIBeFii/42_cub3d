/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:43:40 by mibernar          #+#    #+#             */
/*   Updated: 2023/09/05 12:41:45 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	movement_up_down(t_player *player, t_map *map, int key_code)
{
	if (key_code == W_KEY)
	{
		if (map->map[(int)(player->pos.y + player->direction.y * MOVE_SPEED)]
			[(int)(player->pos.x)] != '1')
			player->pos.y += player->direction.y * MOVE_SPEED;
		if (map->map[(int)(player->pos.y)]
			[(int)(player->pos.x + player->direction.x * MOVE_SPEED)] != '1')
			player->pos.x += player->direction.x * MOVE_SPEED;
	}
	else if (key_code == S_KEY)
	{
		if (map->map[(int)(player->pos.y - player->direction.y * MOVE_SPEED)]
			[(int)(player->pos.x)] != '1')
			player->pos.y -= player->direction.y * MOVE_SPEED;
		if (map->map[(int)(player->pos.y)]
			[(int)(player->pos.x - player->direction.x * MOVE_SPEED)] != '1')
			player->pos.x -= player->direction.x * MOVE_SPEED;
	}
}

void	movement_left_right(t_player *player, t_map *map, int key_code)
{
	if (key_code == D_KEY)
	{
		if (map->map[(int)(player->pos.y + player->direction.x * MOVE_SPEED)]
			[(int)(player->pos.x)] != '1')
			player->pos.y += player->direction.x * MOVE_SPEED;
		if (map->map[(int)(player->pos.y)]
			[(int)(player->pos.x - player->direction.y * MOVE_SPEED)] != '1')
			player->pos.x -= player->direction.y * MOVE_SPEED;
	}
	else if (key_code == A_KEY)
	{
		if (map->map[(int)(player->pos.y - player->direction.x * MOVE_SPEED)]
			[(int)(player->pos.x)] != '1')
			player->pos.y -= player->direction.x * MOVE_SPEED;
		if (map->map[(int)(player->pos.y)]
			[(int)(player->pos.x + player->direction.y * MOVE_SPEED)] != '1')
			player->pos.x += player->direction.y * MOVE_SPEED;
	}
}

void	camera_changes(int key_code, t_player *player)
{
	double	old_dir_x;
	double	old_camera_x;

	old_dir_x = player->direction.x;
	old_camera_x = player->camera.x;
	if (key_code == L_ARROW)
	{
		player->direction.x = player->direction.x * cos(-ROT_SPEED)
			- player->direction.y * sin(-ROT_SPEED);
		player->direction.y = old_dir_x * sin(-ROT_SPEED)
			+ player->direction.y * cos(-ROT_SPEED);
		player->camera.x = player->camera.x * cos(-ROT_SPEED)
			- player->camera.y * sin(-ROT_SPEED);
		player->camera.y = old_camera_x * sin(-ROT_SPEED)
			+ player->camera.y * cos(-ROT_SPEED);
	}
	else if (key_code == R_ARROW)
	{
		player->direction.x = player->direction.x * cos(ROT_SPEED)
			- player->direction.y * sin(ROT_SPEED);
		player->direction.y = old_dir_x * sin(ROT_SPEED)
			+ player->direction.y * cos(ROT_SPEED);
		player->camera.x = player->camera.x * cos(ROT_SPEED)
			- player->camera.y * sin(ROT_SPEED);
		player->camera.y = old_camera_x * sin(ROT_SPEED)
			+ player->camera.y * cos(ROT_SPEED);
	}
}
