/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:06:34 by mibernar          #+#    #+#             */
/*   Updated: 2023/05/19 16:59:31 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	keys(int key_code, t_game *mlx)
{
	if (key_code == ESC_KEY)
		close_window(mlx);
	else if (key_code == W_KEY || key_code == A_KEY || key_code == S_KEY
		|| key_code == D_KEY || key_code == L_ARROW || key_code == R_ARROW)
		move_dot(key_code, mlx);
	return (0);
}
