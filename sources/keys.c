/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:53:57 by mibernar          #+#    #+#             */
/*   Updated: 2023/08/28 16:26:29 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	keys(int key_code, t_game *mlx)
{
	if (key_code == ESC_KEY)
		close_window(mlx);
	else if (key_code == W_KEY || key_code == A_KEY || key_code == S_KEY
		|| key_code == D_KEY || key_code == L_ARROW || key_code == R_ARROW)
		movements(key_code, &mlx->map.player);
	return (0);
}
