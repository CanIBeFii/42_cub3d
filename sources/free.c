/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:05:38 by fialexan          #+#    #+#             */
/*   Updated: 2023/08/23 16:09:25 by mibernar         ###   ########.fr       */
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
	if (mlx->map.map != NULL)
		free_double_array(mlx->map.map);
	if (mlx->info.no)
		free(mlx->info.no);
	if (mlx->info.so)
		free(mlx->info.so);
	if (mlx->info.ea)
		free(mlx->info.ea);
	if (mlx->info.we)
		free(mlx->info.we);
	// mlx_destroy_window(mlx->mlx_ptr, mlx->window);
	// mlx_destroy_display(mlx->mlx_ptr);
	// free (mlx->mlx_ptr);
}
