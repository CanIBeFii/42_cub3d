/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fialexan <fialexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:53:57 by mibernar          #+#    #+#             */
/*   Updated: 2023/08/30 14:43:22 by fialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	keys(int key_code, t_game *mlx)
{
	if (key_code == ESC_KEY)
		close_window(mlx);
	else if (key_code == W_KEY || key_code == S_KEY)
		movement_up_down(&mlx->map.player, &mlx->map, key_code);
	else if (key_code == A_KEY || key_code == D_KEY)
		movement_left_right(&mlx->map.player, &mlx->map, key_code);
	else if (key_code == L_ARROW || key_code == R_ARROW)
		camera_changes(key_code, &mlx->map.player);
	return (0);
}
