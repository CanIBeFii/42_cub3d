/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:43:40 by mibernar          #+#    #+#             */
/*   Updated: 2023/08/25 17:20:21 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	movements(int key_code, t_player *player)
{
	if (key_code == W_KEY)
	{
		player->pos.x += player->direction.x * MOVE_SPEED;
		player->pos.y += player->direction.y * MOVE_SPEED;
	}
	if (key_code == S_KEY)
	{
		player->pos.x -= player->direction.x * MOVE_SPEED;
		player->pos.y -= player->direction.y * MOVE_SPEED;
	}
	/*needs code for left and right strafe
	*
	*
	*
	*/
	if (key_code == L_ARROW)
	{
		player->direction.x = player->direction.x * cos(-ROT_SPEED) - player->direction.y * sin(-ROT_SPEED);
		player->direction.y = player->direction.x * sin(-ROT_SPEED) + player->direction.y * cos(-ROT_SPEED);
		player->camera.x = player->camera.x * cos(-ROT_SPEED) - player->camera.y * sin(-ROT_SPEED);
		player->camera.y = player->camera.x * sin(-ROT_SPEED) + player->camera.y * cos(-ROT_SPEED);
	}
	if (key_code == R_ARROW)
	{
		player->direction.x = player->direction.x * cos(ROT_SPEED) - player->direction.y * sin(ROT_SPEED);
		player->direction.y = player->direction.x * sin(ROT_SPEED) + player->direction.y * cos(ROT_SPEED);
		player->camera.x = player->camera.x * cos(ROT_SPEED) - player->camera.y * sin(ROT_SPEED);
		player->camera.y = player->camera.x * sin(ROT_SPEED) + player->camera.y * cos(ROT_SPEED);
	}
}
