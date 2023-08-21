/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fialexan <fialexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:05:38 by fialexan          #+#    #+#             */
/*   Updated: 2023/08/21 14:16:51 by fialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_double_array(char **array)
{
	int	index;

	index = 0;
	if (array == NULL)
		return ;
	while (array[index] != NULL)
	{
		free(array[index]);
		index++;
	}
	free(array);
	array = NULL;
}

void	free_game(t_game *mlx)
{
	(void)mlx;
	if (mlx->map.map != NULL)
		free_double_array(mlx->map.map);
	// mlx_destroy_window(mlx->mlx_ptr, mlx->window);
	// mlx_destroy_display(mlx->mlx_ptr);
	// free (mlx->mlx_ptr);
}
