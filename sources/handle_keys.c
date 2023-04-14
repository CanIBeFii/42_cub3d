/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:06:34 by mibernar          #+#    #+#             */
/*   Updated: 2023/04/14 15:05:11 by mibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	keys(int key_code, t_game *mlx)
{
	if (key_code == 65307)
		close_window(mlx);
	else if (key_code == 119 || key_code == 97 || key_code == 115
		|| key_code == 100)
		move_dot(key_code, mlx);
	return (0);
}
