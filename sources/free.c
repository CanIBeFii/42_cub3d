/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:05:38 by fialexan          #+#    #+#             */
/*   Updated: 2023/09/01 12:40:47 by mibernar         ###   ########.fr       */
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
		mlx_destroy_image(mlx->mlx_ptr, mlx->info.no_texture.img);
	if (mlx->info.so)
		mlx_destroy_image(mlx->mlx_ptr, mlx->info.so_texture.img);
	if (mlx->info.ea)
		mlx_destroy_image(mlx->mlx_ptr, mlx->info.ea_texture.img);
	if (mlx->info.we)
		mlx_destroy_image(mlx->mlx_ptr, mlx->info.we_texture.img);
	mlx_destroy_window(mlx->mlx_ptr, mlx->window);
	mlx_destroy_display(mlx->mlx_ptr);
	free (mlx->mlx_ptr);
}
